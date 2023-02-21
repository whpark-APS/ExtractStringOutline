using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using static System.Windows.Forms.VisualStyles.VisualStyleElement;
using ExtractStringOutline;

namespace Example
{
	public partial class MainForm : Form
	{
		public MainForm()
		{
			InitializeComponent();
			// str : A ~ Z
			StringBuilder sb = new StringBuilder();
			for (char c = 'A'; c <= 'Z'; c++)
			{
				sb.Append(c);
			}
			textContent.Text = sb.ToString();
			textFontName.Text = "Segoe UI";
			textFontSize.Text = "9";
		}

		private void btnSelectFont_Click(object sender, EventArgs e)
		{
			System.Windows.Forms.FontDialog fontDialog = new System.Windows.Forms.FontDialog();
			fontDialog.ShowColor = true;

			//fontDialog.Font = textBox1.Font;
			//fontDialog.Color = textBox1.ForeColor;

			if (fontDialog.ShowDialog() != DialogResult.Cancel)
			{
				textFontName.Text = fontDialog.Font.Name.ToString();
				textFontSize.Text = fontDialog.Font.Size.ToString();
			}
		}

		private void btnGenerate_Click(object sender, EventArgs e)
		{
			//xExtractStringOutline.ExtractStringOutline(textContent.Text);
			try
			{

				xExtractStringOutline ex = new xExtractStringOutline();
				ex.ExtractStringOutline(true);
			} catch (Exception ex)
			{

			}
		}
	}
}
