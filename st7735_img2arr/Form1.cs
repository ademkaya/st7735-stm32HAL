using System;
using System.Drawing;
using System.IO;

using System.Windows.Forms;

namespace st7735_img2arr
{
    public partial class Form1 : Form
    {
        DirectoryInfo di;
        string filePath = string.Empty;
        string fileName = string.Empty;
        UInt32[] array;
        public Form1()
        {
            InitializeComponent();
        }

        private void btn_import_Click(object sender, EventArgs e)
        {
            if(array!=null)
                Array.Clear(array, 0, array.Length);
            filePath = string.Empty;
            filePath = string.Empty;

            using (OpenFileDialog fd = new OpenFileDialog())
            {
                string path = Environment.GetFolderPath(Environment.SpecialFolder.Desktop);
                fd.InitialDirectory = path;
                fd.Filter = "Bmp File| *.bmp| Jpg File| *.jpg |Png File| *.png|All Files|*.*";
                if (fd.ShowDialog() == DialogResult.OK)
                {
                    filePath = fd.FileName;
                    fileName = fd.SafeFileName;
                    di =  Directory.GetParent(filePath);
                }
                pBox.Image = Image.FromFile(filePath);
            }


        }

        private void txt_convert_Click(object sender, EventArgs e)
        {            
            using (Image img = Image.FromFile(filePath))
            {
                Size sz = new Size(Convert.ToInt32(txt_width.Text), Convert.ToInt32(txt_height.Text));
                Bitmap bmp = new Bitmap(img, sz);
                array = new UInt32[sz.Width*sz.Height];

                bmp2arr(bmp,array);
            }            
        }

        private void bmp2arr(Bitmap bmp, uint[] array)
        {
            for (int y = 0; y < bmp.Height; y++)
            {
                for (int x = 0; x < bmp.Width; x++)
                {


                    byte R = bmp.GetPixel(x, y).R;
                    byte G = bmp.GetPixel(x, y).G;
                    byte B = bmp.GetPixel(x, y).B;
                    array[y*bmp.Width+x] = (uint)((R & 0xF8) << 8) | (uint)((G & 0xFC) << 3) | (uint)(B >> 3);
                }
            }

            array2text(di.FullName, array);
        }


        private void array2text(string path,uint[] arr)
        {
            using (StreamWriter sw = new StreamWriter(string.Concat(path, "/output.txt"), false))
            {
                sw.Write("uint16_t rgbArray[]={");
                for(uint i = 0; i < arr.Length; i++)
                {
                    string val = string.Empty;
                    if (i == arr.Length-1)
                        val = "0x" + arr[i].ToString("x");
                    else
                        val = "0x" + arr[i].ToString("x") + ",";

                    sw.Write(val);
                }
                sw.Write("};");
            }
            MessageBox.Show("Done!");
        }
    }
}
