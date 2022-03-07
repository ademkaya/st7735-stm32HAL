
namespace st7735_img2arr
{
    partial class Form1
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.pBox = new System.Windows.Forms.PictureBox();
            this.txt_height = new System.Windows.Forms.TextBox();
            this.txt_width = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.btn_import = new System.Windows.Forms.Button();
            this.txt_convert = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pBox)).BeginInit();
            this.SuspendLayout();
            // 
            // pBox
            // 
            this.pBox.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch;
            this.pBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.pBox.Location = new System.Drawing.Point(12, 12);
            this.pBox.Name = "pBox";
            this.pBox.Size = new System.Drawing.Size(226, 292);
            this.pBox.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pBox.TabIndex = 0;
            this.pBox.TabStop = false;
            // 
            // txt_height
            // 
            this.txt_height.Location = new System.Drawing.Point(311, 37);
            this.txt_height.Name = "txt_height";
            this.txt_height.Size = new System.Drawing.Size(52, 22);
            this.txt_height.TabIndex = 1;
            this.txt_height.Text = "160";
            // 
            // txt_width
            // 
            this.txt_width.Location = new System.Drawing.Point(253, 37);
            this.txt_width.Name = "txt_width";
            this.txt_width.Size = new System.Drawing.Size(52, 22);
            this.txt_width.TabIndex = 2;
            this.txt_width.Text = "128";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(259, 12);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(46, 17);
            this.label1.TabIndex = 3;
            this.label1.Text = "label1";
            // 
            // btn_import
            // 
            this.btn_import.Location = new System.Drawing.Point(253, 76);
            this.btn_import.Name = "btn_import";
            this.btn_import.Size = new System.Drawing.Size(110, 31);
            this.btn_import.TabIndex = 4;
            this.btn_import.Text = "import";
            this.btn_import.UseVisualStyleBackColor = true;
            this.btn_import.Click += new System.EventHandler(this.btn_import_Click);
            // 
            // txt_convert
            // 
            this.txt_convert.Location = new System.Drawing.Point(253, 273);
            this.txt_convert.Name = "txt_convert";
            this.txt_convert.Size = new System.Drawing.Size(110, 31);
            this.txt_convert.TabIndex = 5;
            this.txt_convert.Text = "convert";
            this.txt_convert.UseVisualStyleBackColor = true;
            this.txt_convert.Click += new System.EventHandler(this.txt_convert_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(380, 323);
            this.Controls.Add(this.txt_convert);
            this.Controls.Add(this.btn_import);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txt_width);
            this.Controls.Add(this.txt_height);
            this.Controls.Add(this.pBox);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.pBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pBox;
        private System.Windows.Forms.TextBox txt_height;
        private System.Windows.Forms.TextBox txt_width;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button btn_import;
        private System.Windows.Forms.Button txt_convert;
    }
}

