namespace DataExporter
{
    partial class MainWindow
    {
        /// <summary>
        /// 필수 디자이너 변수입니다.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 사용 중인 모든 리소스를 정리합니다.
        /// </summary>
        /// <param name="disposing">관리되는 리소스를 삭제해야 하면 true이고, 그렇지 않으면 false입니다.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form 디자이너에서 생성한 코드

        /// <summary>
        /// 디자이너 지원에 필요한 메서드입니다. 
        /// 이 메서드의 내용을 코드 편집기로 수정하지 마세요.
        /// </summary>
        private void InitializeComponent()
        {
            this.Button_ExportExcelToXml = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.TextBox_ExcelPath = new System.Windows.Forms.TextBox();
            this.TextBox_XmlDir = new System.Windows.Forms.TextBox();
            this.Button_FindExcel = new System.Windows.Forms.Button();
            this.Button_FileXmlDir = new System.Windows.Forms.Button();
            this.TextBox_Log = new System.Windows.Forms.TextBox();
            this.Button_ClearLog = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // Button_ExportExcelToXml
            // 
            this.Button_ExportExcelToXml.Location = new System.Drawing.Point(12, 87);
            this.Button_ExportExcelToXml.Name = "Button_ExportExcelToXml";
            this.Button_ExportExcelToXml.Size = new System.Drawing.Size(162, 23);
            this.Button_ExportExcelToXml.TabIndex = 0;
            this.Button_ExportExcelToXml.Text = "Export Excel to Xml";
            this.Button_ExportExcelToXml.UseVisualStyleBackColor = true;
            this.Button_ExportExcelToXml.Click += new System.EventHandler(this.Button_ExportExcelToXml_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(13, 25);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(93, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "Excel 파일 경로";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(13, 60);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(163, 12);
            this.label2.TabIndex = 2;
            this.label2.Text = "Xml 파일이 추출될 폴더 경로";
            // 
            // TextBox_ExcelPath
            // 
            this.TextBox_ExcelPath.HideSelection = false;
            this.TextBox_ExcelPath.Location = new System.Drawing.Point(180, 25);
            this.TextBox_ExcelPath.Name = "TextBox_ExcelPath";
            this.TextBox_ExcelPath.ReadOnly = true;
            this.TextBox_ExcelPath.Size = new System.Drawing.Size(402, 21);
            this.TextBox_ExcelPath.TabIndex = 3;
            // 
            // TextBox_XmlDir
            // 
            this.TextBox_XmlDir.HideSelection = false;
            this.TextBox_XmlDir.Location = new System.Drawing.Point(182, 60);
            this.TextBox_XmlDir.Name = "TextBox_XmlDir";
            this.TextBox_XmlDir.ReadOnly = true;
            this.TextBox_XmlDir.Size = new System.Drawing.Size(400, 21);
            this.TextBox_XmlDir.TabIndex = 4;
            this.TextBox_XmlDir.Text = "XmlFiles/";
            // 
            // Button_FindExcel
            // 
            this.Button_FindExcel.Location = new System.Drawing.Point(588, 23);
            this.Button_FindExcel.Name = "Button_FindExcel";
            this.Button_FindExcel.Size = new System.Drawing.Size(75, 23);
            this.Button_FindExcel.TabIndex = 5;
            this.Button_FindExcel.Text = "찾아보기";
            this.Button_FindExcel.UseVisualStyleBackColor = true;
            this.Button_FindExcel.Click += new System.EventHandler(this.Button_FindExcel_Click);
            // 
            // Button_FileXmlDir
            // 
            this.Button_FileXmlDir.Location = new System.Drawing.Point(588, 58);
            this.Button_FileXmlDir.Name = "Button_FileXmlDir";
            this.Button_FileXmlDir.Size = new System.Drawing.Size(75, 23);
            this.Button_FileXmlDir.TabIndex = 6;
            this.Button_FileXmlDir.Text = "찾아보기";
            this.Button_FileXmlDir.UseVisualStyleBackColor = true;
            this.Button_FileXmlDir.Click += new System.EventHandler(this.Button_FileXmlDir_Click);
            // 
            // TextBox_Log
            // 
            this.TextBox_Log.HideSelection = false;
            this.TextBox_Log.Location = new System.Drawing.Point(12, 125);
            this.TextBox_Log.Multiline = true;
            this.TextBox_Log.Name = "TextBox_Log";
            this.TextBox_Log.ReadOnly = true;
            this.TextBox_Log.Size = new System.Drawing.Size(651, 282);
            this.TextBox_Log.TabIndex = 7;
            // 
            // Button_ClearLog
            // 
            this.Button_ClearLog.Location = new System.Drawing.Point(12, 415);
            this.Button_ClearLog.Name = "Button_ClearLog";
            this.Button_ClearLog.Size = new System.Drawing.Size(162, 23);
            this.Button_ClearLog.TabIndex = 8;
            this.Button_ClearLog.Text = "Clear Log";
            this.Button_ClearLog.UseVisualStyleBackColor = true;
            this.Button_ClearLog.Click += new System.EventHandler(this.Button_ClearLog_Click);
            // 
            // MainWindow
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(675, 450);
            this.Controls.Add(this.Button_ClearLog);
            this.Controls.Add(this.TextBox_Log);
            this.Controls.Add(this.Button_FileXmlDir);
            this.Controls.Add(this.Button_FindExcel);
            this.Controls.Add(this.TextBox_XmlDir);
            this.Controls.Add(this.TextBox_ExcelPath);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.Button_ExportExcelToXml);
            this.Name = "MainWindow";
            this.Text = "Data Exporter";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button Button_ExportExcelToXml;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox TextBox_ExcelPath;
        private System.Windows.Forms.TextBox TextBox_XmlDir;
        private System.Windows.Forms.Button Button_FindExcel;
        private System.Windows.Forms.Button Button_FileXmlDir;
        private System.Windows.Forms.TextBox TextBox_Log;
        private System.Windows.Forms.Button Button_ClearLog;
    }
}

