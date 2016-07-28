//Trevor Cargile
//813542789
//CompE361 - Lab 6!


using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Solution_Lab6
{
	public partial class Form1 : Form
	{
        int FormHeight;
        int size;
        int enterflag = 0;
        int amountselected = 0;
        int rowselected = -1;
        int randrowvalue;
        int columnsmax = 0;
        int botflag = 0;
        int userscore = 0;
        int compscore = 0;
        int startmenuflag = 1;
        int whowon = 0;
        int resizing = 0;
        int endflag = 0;
        Font font = new Font("Tahoma", 12);
        Font font2 = new Font("Tahoma", 9);
        Point stringposition;
        //Point stringposition2;
        //Point stringposition3;

        string winphrase = "lol";
        string losephrase = "You lose!";
        //string userscore2;
        //string compscore2;

        List<int> selectSequence = new List<int>();
        List<int> amountSequence = new List<int>();
        List<int> columnSequence = new List<int>();
        
		Rectangle[,] rectArray;
		int rows = 5, columns = 10;
		Pen pen = new Pen(Color.Red, 2);
        Pen selectPen = new Pen(Color.Green, 2);
        Pen eraserPen = new Pen(Color.Pink, 2);
        Brush brush = new SolidBrush(Color.Black);

		public Form1()
		{
			InitializeComponent();
            this.DoubleBuffered = true;
            eraserPen = new Pen(BackColor, 2);

            FormHeight = NimLogo.Height + menuStrip1.Height;

            Random randrows = new Random();
            randrowvalue = randrows.Next(rows) + 1;

            Graphics g = CreateGraphics();
            SizeF stringSize;
            font = new System.Drawing.Font(font.FontFamily, ClientSize.Width / 20);
            if (whowon == 1)
                stringSize = g.MeasureString(winphrase, font);
            else
                stringSize = g.MeasureString(losephrase, font);
            int x = (int)(ClientSize.Width / 2 - stringSize.Width / 2);
            int y = (int)(ClientSize.Height / 2 - stringSize.Height / 2);
            stringposition = new Point(x, y);

            for (int i = 0; i < (rows); i++)
            {
                columnSequence.Add(randrows.Next(columns) + 1);
            }

            for (int i = 0; i < (columns * rows); i++)
            {
                selectSequence.Add(0);
            }
            for (int i = 0; i < randrowvalue; i++)
            {
                amountSequence.Add(columnSequence[i]);
            }

            for (int r = 0; r < randrowvalue; r++)
            {
                if (columnsmax < columnSequence[r])
                    columnsmax = columnSequence[r];
            }

            size = 10 + panel1.ClientSize.Height / (randrowvalue + 1) / 10 + panel1.ClientSize.Width / (columnsmax + 1) / 10;

            int maxcolsize = 0;
            for (int blah = 0; blah < randrowvalue; blah++)
            {
                if (maxcolsize < amountSequence[blah])
                    maxcolsize = amountSequence[blah];
            }

			rectArray = new Rectangle[columns, rows];

            int itick = 0;
            float dy = panel1.Height / (randrowvalue + 1.0F);
            for (int r = 0; r < randrowvalue; r++)
            {
                float dx = ((float)panel1.Width - (maxcolsize * size)) / (maxcolsize + 1);
                for (int c = 0; c < columnSequence[itick]; c++)
                    rectArray[c, r] = new Rectangle((int)(dx + c * dx + size * c), (int)(FormHeight + dy + r * dy), size, size);
                itick++;
            }
		}

        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            int itick = 0;

            if (endflag == 1)
            {
                if (whowon == 1)
                    g.DrawString(winphrase, font, brush, stringposition);
                else
                    g.DrawString(losephrase, font, brush, stringposition);

                //g.DrawString(compscore2, font, brush, stringposition2);
                //g.DrawString(userscore2, font, brush, stringposition3);
                enterflag = 1;
            }
            if (enterflag == 0)
            {
                for (int r = 0; r < randrowvalue; r++)
                {
                    for (int c = 0; c < columnSequence[itick]; c++)
                    {
                        if (selectSequence[getPosition(c, r)] == 0)
                        {
                            g.DrawRectangle(pen, rectArray[c, r]);
                        }
                        else if (selectSequence[getPosition(c, r)] == 1)
                        {
                            g.DrawRectangle(selectPen, rectArray[c, r]);
                        }
                    }
                    itick++;
                }
                
            }
            else if (enterflag == 1)
            {
                for (int r = 0; r < randrowvalue; r++)
                {
                    for (int c = 0; c < columnSequence[itick]; c++)
                    {
                        if (selectSequence[getPosition(c, r)] == 0)
                        {
                            g.DrawRectangle(pen, rectArray[c, r]);
                        }
                        else if (selectSequence[getPosition(c, r)] == 1)
                        {
                            g.DrawRectangle(eraserPen, rectArray[c, r]);
                            selectSequence[getPosition(c, r)] = 2;
                            amountSequence[r]--;
                        }
                    }
                    itick++;
                }

                int notwinflag = 0;
                for (int nep = 0; nep < randrowvalue; nep++)
                {
                    if (amountSequence[nep] != 0)
                        notwinflag = 1;
                }

                if (notwinflag == 0 && resizing != 1)
                {
                    if (resizing == 0)
                    {
                        if (whowonchecker() == 1)
                        {
                            userscore++;
                            whowon = 1;
                            startmenuflag = 0;
                            resizing = 1;
                        }
                        else
                        {
                            compscore++;
                            whowon = 0;
                            startmenuflag = 0;
                            resizing = 1;
                        }


                        if (endflag != 1)
                        {
                            endgametimer.Enabled = true;

                            winphrase = @"You win!
                             
Scores:
    Me: " + compscore.ToString() + @"
    You: " + userscore.ToString();

                            losephrase = @"You lose!
                             
Scores:
    Me: " + compscore.ToString() + @"
    You: " + userscore.ToString();
                        }
                    }
                }
                else if (notwinflag == 0 && resizing == 1)
                { }
                else
                {
                    amountselected = 0;
                    rowselected = -1;
                    enterflag = 0;
                    resizing = 0;

                    if (botflag == 0)
                        botTurn();
                    else
                    {
                        botflag = 0;
                        startmenuflag = 0;
                    }
                }
            }
        }

        private void setRowsAndColumnsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Changevalueform dlg = new Changevalueform();
            DialogResult dr = dlg.ShowDialog();
            if (dr == System.Windows.Forms.DialogResult.OK)
            {
                columns = dlg.column;
                rows = dlg.row;
            }
        }

        private void newGameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            button_yesfirst.Enabled = false;
            button_nosecond.Enabled = false;
            button_yesfirst.Visible = false;
            button_nosecond.Visible = false;
            label1.Visible = false;
            label1.Enabled = false;
            gofirstlabel.Visible = false;
            gofirstlabel.Enabled = false;
            startgametimer.Stop();
            pretimer.Stop();
            bottimer.Stop();
            endgametimer.Stop();
            label_mescore.Visible = false;
            label_youscore.Visible = false;

            rectArray = new Rectangle[columns, rows];

            amountselected = 0;
            rowselected = -1;
            enterflag = 0;
            endflag = 0;
            botflag = 0;

            startmenuflag = 1;
            startgametimer.Enabled = true;

            Random randrows = new Random();
            randrowvalue = randrows.Next(rows) + 1;

            columnSequence.Clear();
            selectSequence.Clear();
            amountSequence.Clear();

            for (int i = 0; i < (rows); i++)
            {
                columnSequence.Add(randrows.Next(columns) + 1);
            }
            columnSequence.Add(0);

            for (int i = 0; i < (columns * rows); i++)
            {
                selectSequence.Add(0);
            }
            for (int i = 0; i < randrowvalue; i++)
            {
                amountSequence.Add(columnSequence[i]);
            }

            for (int r = 0; r < randrowvalue; r++)
            {
                if (columnsmax < columnSequence[r])
                    columnsmax = columnSequence[r];
            }

            Graphics g = CreateGraphics();
            SizeF stringSize;
            font = new System.Drawing.Font(font.FontFamily, ClientSize.Width / 20);
            if (whowon == 1)
                stringSize = g.MeasureString(winphrase, font);
            else
                stringSize = g.MeasureString(losephrase, font);
            int x = (int)(ClientSize.Width / 2 - stringSize.Width / 2);
            int y = (int)(ClientSize.Height / 2 - stringSize.Height / 2);
            stringposition = new Point(x, y);

            int maxcolsize = 0;
            for (int blah = 0; blah < randrowvalue; blah++)
            {
                if (maxcolsize < amountSequence[blah])
                    maxcolsize = amountSequence[blah];
            }

            g.Dispose();

            size = 10 + panel1.ClientSize.Height / (randrowvalue + 1) / 10 + panel1.ClientSize.Width / (columnsmax + 1) / 10;

            int itick = 0;
            float dy = panel1.Height / (randrowvalue + 1.0F);
            for (int r = 0; r < randrowvalue; r++)
            {
                float dx = ((float)panel1.Width - (maxcolsize * size)) / (maxcolsize + 1);
                for (int c = 0; c < columnSequence[itick]; c++)
                    rectArray[c, r] = new Rectangle((int)(dx + c * dx + size * c), (int)(FormHeight + dy + r * dy), size, size);
                itick++;
            }

            Invalidate();
        }

        private void Form1_Resize(object sender, EventArgs e)
        {
            Graphics g = CreateGraphics();
            int maxcolsize = 0;
            resizing = 1;
            for (int blah = 0; blah < randrowvalue; blah++)
            {
                if (maxcolsize < columnSequence[blah])
                    maxcolsize = columnSequence[blah];
            }

            size = 10 + panel1.ClientSize.Height / (randrowvalue + 1) / 10 + panel1.ClientSize.Width / (columnsmax + 1) / 10;

            int itick = 0;
            float dy = panel1.Height / (randrowvalue + 1.0F);
            for (int r = 0; r < randrowvalue; r++)
            {
                float dx = ((float)panel1.Width - (maxcolsize * size)) / (maxcolsize + 1);
                for (int c = 0; c < columnSequence[itick]; c++)
                    rectArray[c, r] = new Rectangle((int)(dx + c * dx + size * c), (int)(FormHeight + dy + r * dy), size, size);
                itick++;
            }

            SizeF stringSize;
            font = new System.Drawing.Font(font.FontFamily, ClientSize.Width / 20);
            if (whowon == 1)
                stringSize = g.MeasureString(winphrase, font);
            else
                stringSize = g.MeasureString(losephrase, font);
            int x = (int)(ClientSize.Width / 2 - stringSize.Width / 2);
            int y = (int)(ClientSize.Height / 2 - stringSize.Height / 2);
            stringposition = new Point(x, y);

            //stringSize = g.MeasureString(compscore2, font);
            //x = (int)(ClientSize.Width / 2 - stringSize.Width / 2);
            //y = (int)(ClientSize.Height / 3 - stringSize.Height / 3 + y);
            //stringposition2 = new Point(x, y);

            //stringSize = g.MeasureString(userscore2, font);
            //x = (int)(ClientSize.Width / 2 - stringSize.Width / 2);
            //y = (int)(ClientSize.Height / 3 - stringSize.Height / 3 + y);
            //stringposition3 = new Point(x, y);

            Invalidate();
            this.DoubleBuffered = true;
        }

        private void Form1_MouseDown(object sender, MouseEventArgs e)
        {
            if (startmenuflag == 0)
            {
                if (e.Button == MouseButtons.Left)
                {
                    Graphics g = this.CreateGraphics();
                    if (botflag == 1)
                    { }    //MessageBox.Show("Error. Wait for your opponent to finish.");
                    else
                    {
                        for (int c = 0; c < columns; c++)
                            for (int r = 0; r < rows; r++)
                            {
                                if (rectArray[c, r].Contains(e.Location))
                                {
                                    if (rowselected != -1 && (r != rowselected) && selectSequence[getPosition(c, r)] != 2)
                                    {
                                        MessageBox.Show("Error. You must choose a token from the same row.");
                                    }
                                    else if (selectSequence[getPosition(c, r)] == 2)
                                    { }
                                    else if (selectSequence[getPosition(c, r)] == 1)
                                    {
                                        g.DrawRectangle(pen, rectArray[c, r]);
                                        selectSequence[getPosition(c, r)] = 0;
                                        amountselected--;
                                        if (amountselected == 0)
                                            rowselected = -1;
                                    }
                                    else if (selectSequence[getPosition(c, r)] == 0)
                                    {
                                        g.DrawRectangle(selectPen, rectArray[c, r]);
                                        selectSequence[getPosition(c, r)] = 1;
                                        amountselected++;
                                        rowselected = r;
                                    }
                                    //NimLogo.Text = getPosition(c, r).ToString();
                                }
                            }
                    }
                }
                else if (e.Button == MouseButtons.Right)
                {
                    if (amountselected == 0)
                    { }
                    else
                    {
                        enterflag = 1;
                        Invalidate();
                    }
                }
            }
        }

        private void changeBackColorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColorDialog cdlg = new ColorDialog();
            DialogResult dr = cdlg.ShowDialog();
            if (dr == System.Windows.Forms.DialogResult.OK)
            {
                BackColor = cdlg.Color;
                eraserPen = new Pen(cdlg.Color, 2);
            }
            resizing = 1;
        }

        private void changeTokenColorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColorDialog cdlg = new ColorDialog();
            DialogResult dr = cdlg.ShowDialog();
            if (dr == System.Windows.Forms.DialogResult.OK)
                pen = new Pen(cdlg.Color, 2);

            resizing = 1;
            Invalidate();
        }

        private void selectedTokenColorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColorDialog cdlg = new ColorDialog();
            DialogResult dr = cdlg.ShowDialog();
            if (dr == System.Windows.Forms.DialogResult.OK)
                selectPen = new Pen(cdlg.Color, 2);

            resizing = 1;
            Invalidate();
        }

        private void fontColorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColorDialog cdlg = new ColorDialog();
            DialogResult dr = cdlg.ShowDialog();
            if (dr == System.Windows.Forms.DialogResult.OK)
                NimLogo.ForeColor = cdlg.Color;

            resizing = 1;
            Invalidate();
        }

        private void changeScoreFontToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FontDialog dlg = new FontDialog();
            DialogResult dr = dlg.ShowDialog();
            if (dr == System.Windows.Forms.DialogResult.OK)
            {
                NimLogo.Font = dlg.Font;
                gofirstlabel.Font = dlg.Font;
            }
            resizing = 1;
            Invalidate();
        }

        private void botTurn()
        {
            int xorvalue = 0;
            int testvalued = 0;
            int amountneederase = 0;
            int startposition = 0;
            int startpositionbefore = 0;
            int testflag = -1;
            int correctmatch = -1;
            botflag = 1;

            //stuff for compare thingy
            int startposition2 = 0;
            int startpositionbefore2 = 0;


            int[] valuechanged = new int[10];
            int[] valuechanged2 = new int[10];
            int[] valuetestchanged = new int[10];

            for (int i = 0; i < 10; i++)
            {
                valuechanged[i] = 0;
            }

            for (int i = 0; i < 10; i++)
            {
                valuechanged2[i] = 0;
            }

            for (int i = 0; i < randrowvalue; i++)
            {
                if (i == 0)
                    xorvalue = amountSequence[i];
                else
                    xorvalue = amountSequence[i] ^ xorvalue;
            }

            int needxor = xorvalue;
            if (xorvalue == 0)
                testflag = -1;
            else
            {
                for (int j = 0; xorvalue != 0; j++)
                {
                    for (int i = 1; i <= xorvalue; i = i * 2)
                        startpositionbefore = i;

                    startposition = (int)(Math.Log10(startpositionbefore) / Math.Log10(2));

                    valuechanged[9 - startposition] = 1;

                    if (testflag == -1)
                        testflag = (9 - startposition);

                    xorvalue = xorvalue - startpositionbefore;
                }
            }

            if (testflag != -1)
            {
                for (int x = 0; x < randrowvalue; x++)
                {
                    testvalued = amountSequence[x];
                    for (int k = 0; testvalued != 0; k++)
                    {
                        for (int i = 1; i <= testvalued; i = i * 2)
                            startpositionbefore = i;

                        startposition = (int)(Math.Log10(startpositionbefore) / Math.Log10(2));

                        valuetestchanged[9 - startposition] = 1;
                        testvalued = testvalued - startpositionbefore;

                        if ((9 - startposition) == testflag)
                        {
                            correctmatch = x;
                            x = randrowvalue;
                        }
                    }
                }
            }

            string testvalue = null;
            for (int i = 0; i < 10; i++)
            {
                if (i == 0)
                    testvalue = valuechanged[i].ToString();
                else
                    testvalue = testvalue + valuechanged[i].ToString();
            }

            if (correctmatch != -1)
            {
                string testvalue2 = null;
                int rowvalue = amountSequence[correctmatch];
                for (int i = 0; i < 10; i++)
                {
                    for (int j = 0; rowvalue != 0; j++)
                    {
                        for (int k = 1; k <= rowvalue; k = k * 2)
                            startpositionbefore2 = k;

                        startposition2 = (int)(Math.Log10(startpositionbefore2) / Math.Log10(2));

                        valuechanged2[9 - startposition2] = 1;

                        if (testflag == -1)
                            testflag = (9 - startposition2);

                        rowvalue = rowvalue - startpositionbefore2;
                    }
                }


                int u = 0;
                for (int tick = 0; tick < 10; tick++)
                {
                    if (valuechanged[tick] == 1)
                    {
                        u = tick;
                        tick = 10;
                    }
                }



                //convert row needed to binary after change from xor
                for (int tick2 = 0; tick2 < 10; tick2++)
                {
                    if (valuechanged[tick2] == 1)
                    {
                        if (valuechanged2[tick2] == 1)
                            valuechanged2[tick2] = 0;
                        else
                            valuechanged2[tick2] = 1;
                    }
                }


                int testvalue3 = 0;
                int v = 1;
                for (int tick3 = 0; tick3 < 10; tick3++)
                {
                    testvalue3 += valuechanged2[9 - tick3] * v;
                    v *= 2;
                }


                amountneederase = amountSequence[correctmatch] - testvalue3;

                for (int i = 0; i < 10; i++)
                {
                    if (i == 0)
                        testvalue2 = valuechanged2[i].ToString();
                    else
                        testvalue2 = testvalue2 + valuechanged2[i].ToString();
                }


                //NimLogo.Text = testvalue + " " + testvalue2 + " " + needxor.ToString() + " " + u.ToString() + " " + amountselected.ToString() + " " + testvalue3.ToString() + " " + amountneederase.ToString() + " " + amountSequence[correctmatch].ToString() + " " + correctmatch.ToString() + " " + selectSequence[getPosition(1, 0)].ToString() + " " + selectSequence[getPosition(2, 0)].ToString() + " " + selectSequence[getPosition(3, 0)].ToString();
                int cr = 0;
                for (int c = 0; c < amountSequence[correctmatch]; c++)
                {
                    if (selectSequence[getPosition(cr, correctmatch)] == 0)
                    {
                        selectSequence[getPosition(cr, correctmatch)] = 1;
                        amountneederase--;
                    }
                    if (selectSequence[getPosition(c, correctmatch)] == 2)
                        c--;
                    if (amountneederase == 0)
                        c = amountSequence[correctmatch];

                    cr++;
                }
                pretimer.Enabled = true;
            }
            else
            {
                Random rand = new Random();
                int randnum = rand.Next(randrowvalue);
                for (int xyz = 0; amountSequence[randnum] == 0; xyz++)
                {
                    randnum = rand.Next(randrowvalue);
                }
                //NimLogo.Text = randnum.ToString() + " " + amountSequence[randnum].ToString();

                int randcol = rand.Next(amountSequence[randnum] - 1) + 1;

                int cr = 0;
                for (int c = 0; c < randcol; c++)
                {
                    if (selectSequence[getPosition(cr, randnum)] == 0)
                        selectSequence[getPosition(cr, randnum)] = 1;
                    if (selectSequence[getPosition(cr, randnum)] == 2)
                        c--;

                    cr++;
                }
                pretimer.Enabled = true;
            }
        }

        private int getPosition(int c, int r)
        {
            int position = 0;
            for (int y = 0; y < r; y++)
                position += columnSequence[y];
            for (int y = 0; y < c; y++)
                position += 1;

            return position;
        }

        private void bottimer_Tick(object sender, EventArgs e)
        {
            enterflag = 1;
            bottimer.Enabled = false;
            Invalidate();
        }

        private void pretimer_Tick(object sender, EventArgs e)
        {
            bottimer.Enabled = true;
            pretimer.Enabled = false;
            Invalidate();
        }

        private void button_yesfirst_Click(object sender, EventArgs e)
        {
            startmenuflag = 0;
            button_yesfirst.Enabled = false;
            button_nosecond.Enabled = false;
            button_yesfirst.Visible = false;
            button_nosecond.Visible = false;
            label1.Visible = false;
            label1.Enabled = false;
            gofirstlabel.Visible = false;
            gofirstlabel.Enabled = false;
            startgametimer.Enabled = false;
            label_mescore.Visible = false;
            label_youscore.Visible = false;
            label_mescore.Enabled = false;
            label_youscore.Enabled = false;
        }

        private void button_nosecond_Click(object sender, EventArgs e)
        {
            button_yesfirst.Enabled = false;
            button_nosecond.Enabled = false;
            button_yesfirst.Visible = false;
            button_nosecond.Visible = false;
            label1.Visible = false;
            label1.Enabled = false;
            gofirstlabel.Visible = false;
            gofirstlabel.Enabled = false;
            label_mescore.Visible = false;
            label_youscore.Visible = false;
            startgametimer.Enabled = false;
            enterflag = 1;
            startmenuflag = 1;
            Invalidate();
        }

        private void startgametimer_Tick(object sender, EventArgs e)
        {
            gofirstlabel.Text = "Would you like to go first?";
            button_yesfirst.Enabled = true;
            button_nosecond.Enabled = true;
            button_yesfirst.Visible = true;
            button_nosecond.Visible = true;
            label1.Visible = true;
            label1.Enabled = true;
            gofirstlabel.Visible = true;
            gofirstlabel.Enabled = true;
            startgametimer.Enabled = false;
            label_mescore.Visible = false;
            label_youscore.Visible = false;
        }

        private void startmenuColorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColorDialog cdlg = new ColorDialog();
            DialogResult dr = cdlg.ShowDialog();
            if (dr == System.Windows.Forms.DialogResult.OK)
            {
                gofirstlabel.BackColor = cdlg.Color;
                label1.BackColor = cdlg.Color;
                label_mescore.BackColor = cdlg.Color;
                label_youscore.BackColor = cdlg.Color;
            }

            resizing = 1;
            Invalidate();
        }

        private void startmenuFontColorToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColorDialog cdlg = new ColorDialog();
            DialogResult dr = cdlg.ShowDialog();
            if (dr == System.Windows.Forms.DialogResult.OK)
            {
                gofirstlabel.ForeColor = cdlg.Color;
                label_mescore.ForeColor = cdlg.Color;
                label_youscore.ForeColor = cdlg.Color;
                brush = new SolidBrush(cdlg.Color);
            }

            resizing = 1;
            Invalidate();
        }

        private void startmenuFontToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FontDialog dlg = new FontDialog();
            DialogResult dr = dlg.ShowDialog();
            if (dr == System.Windows.Forms.DialogResult.OK)
            {
                gofirstlabel.Font = dlg.Font;
                label_mescore.Font = dlg.Font;
                label_youscore.Font = dlg.Font;
                font = dlg.Font;
            }

            resizing = 1;
            Invalidate();
        }

        private void endgametimer_Tick(object sender, EventArgs e)
        {
            endflag = 1;
            startmenuflag = 1;
            Invalidate();
            endgametimer.Stop();
        }

        private int whowonchecker()
        {
            if (botflag == 0)
                return 1;
            else
                return 0;
        }

        private void instructionsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            string aboutstring =
                    @"  Welcome to the game of Nim!
    
                        The point of the game is to be the last one to draw tokens.

                        You are allowed to draw from any row, but are only allowed
                        to draw from the same row. You also must select at least
                        one token. Tokens are represented as red squares(default).
        
                        Left clicking on a token will select it, while right clicking
                        the form will end your turn, and any tokens selected will be
                        deleted from the board.

                        You may changed the color/font of any of the controls by
                        clicking the menu option at the top of the program, going
                        down to 'Change Font and Colors'.

                        Good luck!";

            MessageBox.Show(aboutstring);
                                        
        }

        private void titleFontToolStripMenuItem_Click(object sender, EventArgs e)
        {
            FontDialog dlg = new FontDialog();
            DialogResult dr = dlg.ShowDialog();
            if (dr == System.Windows.Forms.DialogResult.OK)
            {
                NimLogo.Font = dlg.Font;
            }
        }
    }
}
