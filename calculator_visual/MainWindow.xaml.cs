using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using static System.Net.Mime.MediaTypeNames;

namespace calculator_visual
{
    public partial class MainWindow : Window
    {
        Page funct;
        Page par;
        List<function> functions;
        List<Parameter> parameters;
        string Expression;
        Page Funct
        {
            get
            {
                return funct ?? (funct = new Function());
            }
        }
        Page Par
        {
            get
            {
                return par ?? (par = new Param());
            }
        }
        public MainWindow()
        {
            InitializeComponent();
            functions = new List<function>();
            parameters = new List<Parameter>();
        }
        int flag = 0, f2 = 0;
        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (flag==0)
            {
                FrameMain.NavigationService.Navigate(Funct);
                flag = 1;
                f2 = 0;
            }
            else
            {
                function item = ((Function)funct).funclist.SelectedItem as function;
                if (item!=null)
                {
                    if(!functions.Any(s => s.name==item.name && s.definition==item.definition)) functions.Add(item);
                    Add_func_var(item.name);
                }
                FrameMain.Content = null;
                flag = 0;
            }
        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            if(f2==0)
            {
                FrameMain.NavigationService.Navigate(Par);
                flag = 0;
                f2 = 1;
            }
            else
            {
                Parameter item = ((Param)par).paramlist.SelectedItem as Parameter;
                if (item!=null)
                {
                    if (!parameters.Any(s => s.name==item.name)) parameters.Add(item);
                    Add_func_var(item.name);
                }
                FrameMain.Content = null;
                f2 = 0;
            }
        }
        public void Add_func_var(string name)
        {
            if (Expr.Text.Length==0)
            {
                Expr.Text+=name;
                return;
            }
            char prev = Expr.Text[Expr.Text.Length-1];
                if (prev=='!'||prev==')'||prev>='0'&&prev<='9'||prev>='a'&&prev<='z') Expr.Text+="*"+name;
                else if (prev=='.') Expr.Text+="0"+"*"+name;
                else Expr.Text+=name;
        }
        public void Click_Num(object sender, RoutedEventArgs e)
        {
            if (sender is Button)
            {
                Button btn = (Button)sender;
                string text = btn.Content.ToString();
                char prev;
                
                if (flag==1)
                {
                    if(((Function)funct).TextFunc.Text.Length==0)
                    {
                        ((Function)funct).TextFunc.Text+=text;
                        return;
                    }
                    prev = ((Function)funct).TextFunc.Text[((Function)funct).TextFunc.Text.Length-1];
                    if (text[0]>='0' && text[0]<='9')
                    {
                        if (prev=='!'||prev==')'||prev=='π'||prev>='a'&&prev<='z') ((Function)funct).TextFunc.Text+="*"+text;
                        else ((Function)funct).TextFunc.Text+=text;
                    }
                    else
                    {
                        if (prev=='!'||prev==')'||prev>='0'&&prev<='9'||prev>='a'&&prev<='z') ((Function)funct).TextFunc.Text+="*"+text;
                        else if (prev=='.') Expr.Text+="0"+"*"+text;
                        else ((Function)funct).TextFunc.Text+=text;
                    }
                }
                else
                {
                    if(Expr.Text.Length==0)
                    {
                        Expr.Text+=text;
                        return;
                    }
                    prev = Expr.Text[Expr.Text.Length-1];
                    if (text[0]>='0' && text[0]<='9')
                    {
                        if (prev=='!'||prev==')'||prev=='π'||prev>='a'&&prev<='z') Expr.Text+="*"+text;
                        else Expr.Text+=text;
                    }
                    else
                    {
                        if (prev=='!'||prev==')'||prev>='0'&&prev<='9'||prev>='a'&&prev<='z') Expr.Text+="*"+text;
                        else if (prev=='.') Expr.Text+="0"+"*"+text;
                        else Expr.Text+=text;
                    }
                }
            }
        }
        public void Click_trigon(object sender, RoutedEventArgs e)
        {
            if (sender is Button)
            {
                Button btn = (Button)sender;
                string text = btn.Content.ToString();
                char prev;
                
                if (flag==1)
                {
                    if (((Function)funct).TextFunc.Text.Length==0)
                    {
                        ((Function)funct).TextFunc.Text+=text+"(";
                        return;
                    }
                    prev = ((Function)funct).TextFunc.Text[((Function)funct).TextFunc.Text.Length-1];
                    if (prev>='0' && prev<='9' || prev>='a'&&prev<='z'||prev=='π'||prev=='!'||prev==')') ((Function)funct).TextFunc.Text+="*"+text+"(";
                    else if (prev=='.') ((Function)funct).TextFunc.Text+="0"+"*"+text+"(";
                    else ((Function)funct).TextFunc.Text+=text+"(";
                }
                else
                {
                    if (Expr.Text.Length==0)
                    {
                        Expr.Text+=text+"(";
                        return;
                    }
                    prev = Expr.Text[Expr.Text.Length - 1];
                    if (prev>='0' && prev<='9' || prev>='a'&&prev<='z'||prev=='π'||prev=='!'||prev==')') Expr.Text+="*"+text+"(";
                    else if (prev=='.') Expr.Text+="0"+"*"+text+"(";
                    else Expr.Text+=text+"(";
                }
            }
            
        }
        public void Click_operator(object sender,RoutedEventArgs e)
        {
            if (sender is Button)
            {
                Button btn = (Button)sender;
                string text = btn.Content.ToString();
                char prev;
                
                if(flag==1)
                {
                    if (((Function)funct).TextFunc.Text.Length==0)
                    {
                        if(text=="-") ((Function)funct).TextFunc.Text+=text;
                        else if(text==".") ((Function)funct).TextFunc.Text+="0"+text;
                        return;
                    }
                    prev = ((Function)funct).TextFunc.Text[((Function)funct).TextFunc.Text.Length-1];
                    if (text=="!")
                    {
                        if (prev>='0'&&prev<='9'||prev==')'||prev>='a'&&prev<='z') ((Function)funct).TextFunc.Text+=text;
                    }
                    else if (text==".")
                    {
                        if (prev>='0'&&prev<='9') ((Function)funct).TextFunc.Text+=text;
                        else if (prev=='π'|| prev>='a'&&prev<='z' || prev=='!'||prev==')') ((Function)funct).TextFunc.Text+="*"+"0"+text;
                        else if (prev!='.') ((Function)funct).TextFunc.Text+="0"+text;
                    }
                    else
                    {
                        if (prev=='.') ((Function)funct).TextFunc.Text+="0"+text;
                        else if (prev=='('&&text=="-"||!(prev=='-'||prev=='+'||prev=='*'||prev=='/'||prev=='^')) ((Function)funct).TextFunc.Text+=text;
                    }
                }
                else
                {
                    if (Expr.Text.Length==0)
                    {
                        if (text=="-") Expr.Text+=text;
                        else if (text==".") Expr.Text+="0"+text;
                        return;
                    }
                    prev = Expr.Text[Expr.Text.Length - 1];
                    if (text=="!")
                    {
                        if (prev>='0'&&prev<='9'||prev==')'||prev>='a'&&prev<='z') Expr.Text+=text;
                    }
                    else if (text==".")
                    {
                        if (prev>='0'&&prev<='9') Expr.Text+=text;
                        else if (prev=='π'|| prev>='a'&&prev<='z' || prev=='!'||prev==')') Expr.Text+="*"+"0"+text;
                        else if (prev!='.') Expr.Text+="0"+text;
                    }
                    else
                    {
                        if (prev=='.') Expr.Text+="0"+text;
                        else if (prev=='('&&text=="-"||!(prev=='-'||prev=='+'||prev=='*'||prev=='/'||prev=='^')) Expr.Text+=text;
                    }
                }
            }
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            using (StreamWriter file = new StreamWriter(@"C:\Users\yajul\source\repos\calculator\calculator_visual\bin\Debug\input.txt", false))//C:\Users\yajul\source\repos\calculator\x64\Debug\
            {
                file.WriteLine(Expr.Text);
                foreach(function t in functions)
                {
                    file.WriteLine(t.name+" "+t.definition);
                }
                foreach (Parameter par in parameters) file.WriteLine(par.name+" "+par.value.ToString());
                file.Close();
            }
            Process p = new Process();
            p.StartInfo.UseShellExecute = false;
            p.StartInfo.RedirectStandardOutput = true;
            p.StartInfo.FileName = @"C:\Users\yajul\source\repos\calculator\calculator_visual\bin\Debug\calculator.exe";//C:\\Users\\yajul\\source\\repos\\calculator\\x64\\Debug\\
            p.Start();
            p.WaitForExit();
            Expr.Text = "";
            using (StreamReader fil = new StreamReader(@"C:\Users\yajul\source\repos\calculator\calculator_visual\bin\Debug\output.txt", false))//C:\Users\yajul\source\repos\calculator\x64\Debug\
            {
                string output = fil.ReadLine();
                Expr.Text += output;
                fil.Close();
            }
        }

        public void Click_brackets(object sender,RoutedEventArgs e)
        {
            if (sender is Button)
            {
                Button btn = (Button)sender;
                string text = btn.Content.ToString();
                char prev;
                
                if(flag==1)
                {
                    if (((Function)funct).TextFunc.Text.Length==0)
                    {
                        if(text=="(") ((Function)funct).TextFunc.Text+=text;
                        return;
                    }
                    prev = ((Function)funct).TextFunc.Text[((Function)funct).TextFunc.Text.Length-1];
                    if (text=="(")
                    {
                        if (prev>='0' && prev<='9' || prev>='a'&&prev<='z'||prev=='π'||prev=='!'||prev==')') ((Function)funct).TextFunc.Text+="*"+text;
                        else ((Function)funct).TextFunc.Text+=text;
                    }
                    else
                    {
                        if (prev>='0' && prev<='9' || prev>='a'&&prev<='z'||prev=='π'||prev=='!'||prev==')'||prev=='(') ((Function)funct).TextFunc.Text+=text;
                        else if (prev=='.') ((Function)funct).TextFunc.Text+="0"+text;
                    }
                }
                else
                {
                    if (Expr.Text.Length==0)
                    {
                        if (text=="(")  Expr.Text+=text;
                        return;
                    }
                    prev = Expr.Text[Expr.Text.Length - 1];
                    if (text=="(")
                    {
                        if (prev>='0' && prev<='9' || prev>='a'&&prev<='z'||prev=='π'||prev=='!'||prev==')') Expr.Text+="*"+text;
                        else Expr.Text+=text;
                    }
                    else
                    {
                        if (prev>='0' && prev<='9' || prev>='a'&&prev<='z'||prev=='π'||prev=='!'||prev==')'||prev=='(') Expr.Text+=text;
                        else if (prev=='.') Expr.Text+="0"+text;
                    }
                }
            }
        }
    }
}
