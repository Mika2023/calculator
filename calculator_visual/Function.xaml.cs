using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace calculator_visual
{
    /// <summary>
    /// Логика взаимодействия для Function.xaml
    /// </summary>
    public class function
    {
        public string name {  get; set; }
        public string definition { get; set; }
    }
    public partial class Function : Page
    {
        protected string text;
        public string Def {
            get { return text; }
            set { if (value!=null) text = value; }
        }
        List<function> functions;
        public Function()
        {
            InitializeComponent();
            functions = new List<function>();
            funclist.ItemsSource = functions;

        }

        private void ListBox_SelectionChanged(object sender, SelectionChangedEventArgs e)
        {

        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (NameFunc.Text != "" && TextFunc.Text!="")
            {
                function item = new function() { name = NameFunc.Text, definition = TextFunc.Text };
                if(!functions.Any(s=>s.name==item.name && s.definition==item.definition) && item.name.Contains("(x)"))functions.Add(item);
                funclist.Items.Refresh();
                NameFunc.Text = "";
                TextFunc.Text = "";
            }
            else MessageBox.Show("Введите сначала выражение!");
        }
    }
}
