using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Http.Headers;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Media.TextFormatting;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace calculator_visual
{
    /// <summary>
    /// Логика взаимодействия для Param.xaml
    /// </summary>
    public class Parameter
    {
        public string name { get; set; }
        public double value { get; set; }
    }
    public partial class Param : Page
    {
        List<Parameter> parameters;
        public Param()
        {
            InitializeComponent();
            parameters = new List<Parameter>();
            paramlist.ItemsSource = parameters;
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (NamePar.Text != "" && ValuePar.Text!="")
            {
                Parameter item = new Parameter() { name = NamePar.Text, value = Convert.ToDouble(ValuePar.Text) };
                if (!parameters.Any(s => s.name== item.name) && item.name[0]>='a'&&item.name[0]<='z') parameters.Add(item);
                paramlist.Items.Refresh();
                ValuePar.Text = "";
                NamePar.Text = "";
            }
            else MessageBox.Show("Введите сначала выражение!");
        }
    }
}
