
namespace Example
{
    partial class MainForm
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
			this.textContent = new System.Windows.Forms.TextBox();
			this.btnGenerate = new System.Windows.Forms.Button();
			this.btnSelectFont = new System.Windows.Forms.Button();
			this.textFontName = new System.Windows.Forms.TextBox();
			this.listLines = new System.Windows.Forms.ListBox();
			this.textFontSize = new System.Windows.Forms.TextBox();
			this.SuspendLayout();
			// 
			// textContent
			// 
			this.textContent.Location = new System.Drawing.Point(15, 41);
			this.textContent.Name = "textContent";
			this.textContent.Size = new System.Drawing.Size(591, 23);
			this.textContent.TabIndex = 0;
			// 
			// btnGenerate
			// 
			this.btnGenerate.Location = new System.Drawing.Point(13, 70);
			this.btnGenerate.Name = "btnGenerate";
			this.btnGenerate.Size = new System.Drawing.Size(75, 23);
			this.btnGenerate.TabIndex = 1;
			this.btnGenerate.Text = "Extract";
			this.btnGenerate.UseVisualStyleBackColor = true;
			this.btnGenerate.Click += new System.EventHandler(this.btnGenerate_Click);
			// 
			// btnSelectFont
			// 
			this.btnSelectFont.Location = new System.Drawing.Point(13, 12);
			this.btnSelectFont.Name = "btnSelectFont";
			this.btnSelectFont.Size = new System.Drawing.Size(75, 23);
			this.btnSelectFont.TabIndex = 2;
			this.btnSelectFont.Text = "Font";
			this.btnSelectFont.UseVisualStyleBackColor = true;
			this.btnSelectFont.Click += new System.EventHandler(this.btnSelectFont_Click);
			// 
			// textFontName
			// 
			this.textFontName.Location = new System.Drawing.Point(94, 12);
			this.textFontName.Name = "textFontName";
			this.textFontName.ReadOnly = true;
			this.textFontName.Size = new System.Drawing.Size(227, 23);
			this.textFontName.TabIndex = 3;
			// 
			// listLines
			// 
			this.listLines.FormattingEnabled = true;
			this.listLines.ItemHeight = 15;
			this.listLines.Location = new System.Drawing.Point(12, 99);
			this.listLines.Name = "listLines";
			this.listLines.Size = new System.Drawing.Size(168, 409);
			this.listLines.TabIndex = 4;
			// 
			// textFontSize
			// 
			this.textFontSize.Location = new System.Drawing.Point(327, 13);
			this.textFontSize.Name = "textFontSize";
			this.textFontSize.ReadOnly = true;
			this.textFontSize.Size = new System.Drawing.Size(100, 23);
			this.textFontSize.TabIndex = 5;
			// 
			// MainForm
			// 
			this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 15F);
			this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
			this.ClientSize = new System.Drawing.Size(809, 527);
			this.Controls.Add(this.textFontSize);
			this.Controls.Add(this.listLines);
			this.Controls.Add(this.textFontName);
			this.Controls.Add(this.btnSelectFont);
			this.Controls.Add(this.btnGenerate);
			this.Controls.Add(this.textContent);
			this.Name = "MainForm";
			this.Text = "Extract String Outline";
			this.ResumeLayout(false);
			this.PerformLayout();

        }

		#endregion

		private System.Windows.Forms.TextBox textContent;
		private System.Windows.Forms.Button btnGenerate;
		private System.Windows.Forms.Button btnSelectFont;
		private System.Windows.Forms.TextBox textFontName;
		private System.Windows.Forms.ListBox listLines;
		private System.Windows.Forms.TextBox textFontSize;
	}
}

