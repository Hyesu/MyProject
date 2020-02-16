using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace DataExporter
{
    public partial class MainWindow : Form
    {
        private Logger _logger = new Logger();

        public MainWindow()
        {
            InitializeComponent();
            _logger.AddLogger(new LoggerImpl(Log));
        }

        private void ClearLog()
        {
            TextBox_Log.Clear();
        }

        private void Log(string log)
        {
            TextBox_Log.AppendText(log + Environment.NewLine);
        }

        private string GetDirectoryPathFromDialog()
        {
            FolderBrowserDialog fbd = new FolderBrowserDialog();
            DialogResult dlgRes = fbd.ShowDialog();
            if(dlgRes == DialogResult.OK && !string.IsNullOrWhiteSpace(fbd.SelectedPath))
            {
                return fbd.SelectedPath;
            }
            return "";
        }

        private string GetFilePathFromDialog(string filter)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            if(string.IsNullOrEmpty(filter) == false)
            {
                ofd.Filter = filter;
            }
            DialogResult dlgRes = ofd.ShowDialog();
            if(dlgRes == DialogResult.OK)
            {
                return ofd.FileName;
            }
            return "";
        }

        // event handlers
        private void Button_ClearLog_Click(object sender, EventArgs e)
        {
            ClearLog();
        }

        private void Button_FindExcel_Click(object sender, EventArgs e)
        {
            string path = GetFilePathFromDialog("Excel File | *.xlsx;");
            TextBox_ExcelPath.Text = path;
        }

        private void Button_FileXmlDir_Click(object sender, EventArgs e)
        {
            string dirPath = GetDirectoryPathFromDialog();
            TextBox_XmlDir.Text = dirPath;
        }

        private void Button_ExportExcelToXml_Click(object sender, EventArgs e)
        {
            ClearLog();
            Log("Start[Export excel to xml] ...");

            string excelPath = TextBox_ExcelPath.Text;
            if(File.Exists(excelPath) == false)
            {
                Log("-- Fail: not exist excel file: " + excelPath);
                return;
            }

            string xmlDirPath = TextBox_XmlDir.Text;
            if (Directory.Exists(xmlDirPath) == false)
            {
                Log("-- Fail: not exist xml directory path: " + xmlDirPath);
                return;
            }

            ExcelExporter ee = new ExcelExporter(_logger);            
            if (ee.ExportToXml(excelPath, xmlDirPath) == false)
            {
                Log("-- Fail: some error occurred during exporting...");
                return;
            }

            Log("Success: check xml directory(" + xmlDirPath + ")");
        }
    }
}
