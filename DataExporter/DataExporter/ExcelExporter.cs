using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml;
using Microsoft.Office.Interop.Excel;

namespace DataExporter
{
    class ExcelExporter
    {
        private Application _app = null;
        private Logger _logger = null;

        public ExcelExporter(Logger logger)
        {
            _logger = logger;
        }

        public bool ExportToXml(string excelFilePath, string outputDirPath)
        {
            InitializeOffice();

            Workbook wb = _app.Workbooks.Open(excelFilePath, true);
            if(wb == null)
            {
                _logger.Write("fail to open workbook: " + excelFilePath);
                return false;
            }

            foreach(Worksheet sheet in wb.Worksheets)
            {
                string tableName = sheet.Cells[1][1].Value;
                if(string.IsNullOrEmpty(tableName))
                {
                    _logger.Write("sheet[" + sheet.Name + "]: skip");
                    continue;
                }

                if (Export(sheet, outputDirPath, tableName) == false)
                {
                    wb.Close();
                    return false;
                }
            }

            wb.Close();
            return true;
        }

        private void InitializeOffice()
        {
            if(_app != null)
            {
                return;
            }
            _app = new Application();
        }

        private bool Export(Worksheet sheet, string outputDirPath, string tableName)
        {
            List<string> header = ParseHeader(sheet);
            if(header.Count == 0)
            {
                _logger.Write("Fail: sheet[" + sheet.Name + "]: table[" + tableName + "]: empty header. check 2 row");
                return false;
            }

            XmlDocument xml = new XmlDocument();
            XmlNode root = xml.CreateElement(tableName + "s");
            xml.AppendChild(root);

            int row = 3; // data row start index
            while(sheet.Cells[1][row].Value != null)
            {
                XmlNode node = xml.CreateElement(tableName);
                root.AppendChild(node);

                for (int col_z = 0; col_z < header.Count; col_z++)
                {
                    string attrName = header.ElementAt(col_z);
                    var cellValue = sheet.Cells[col_z + 1][row].Value;
                    if(cellValue == null)
                    {
                        // 일단 워닝처리만 해드림
                        _logger.Write("Warning: sheet[" + sheet.Name + "]: cell[" + row + "/" + (col_z + 1) + "] empty cell. check column[" + attrName + "]");
                        cellValue = "";
                    }

                    XmlAttribute attr = xml.CreateAttribute(attrName);
                    attr.Value = cellValue.ToString();
                    node.Attributes.Append(attr);
                }

                row++;
            }
            
            string xmlFilePath = outputDirPath + "/" + tableName + ".xml";            
            xml.Save(xmlFilePath);
            return true;
        }

        private List<string> ParseHeader(Worksheet sheet)
        {
            int headerRow = 2;
            int col = 1;
            List<string> header = new List<string>();            
            while (sheet.Cells[col][headerRow].Value != null)
            {
                header.Add(sheet.Cells[col][headerRow].Value);
                col++;
            }
            return header;
        }
    }
}
