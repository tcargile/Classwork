using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Media;

namespace WindowsFormsApplication1
{
	public partial class Form1 : Form
	{
		SoundPlayer soundPlayer = new SoundPlayer();
		public Form1()
		{
			InitializeComponent();
		}

		private void button_PlaySound_Click(object sender, EventArgs e)
		{
			//soundPlayer.SoundLocation = @"..\..\..\treasure_badges.wav";
			soundPlayer.SoundLocation = "tada.wav";
			soundPlayer.Play();

		}

		private void button1_Click(object sender, EventArgs e)
		{
			Console.WriteLine("In soundplayer2");
			SoundPlayer soundPlayer2 = new SoundPlayer(Properties.Resources.Goodmorn);
			soundPlayer2.PlaySync();
		}
	}
}
