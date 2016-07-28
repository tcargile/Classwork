//Trevor Cargile
//813542789
//LAB 8 - FINAL LAB - COMPE361 - MARINO

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Solution_lab8
{
    public partial class MainWindow : Window
    {
        int columns = 10, rows = 5;
        int rowselected = -1;
        int amountselected = 0;
        int rows_amount = 0;
        int amountneedselected = 0;
        int correctrow = 0;
        int botflag = 0, startflag = 1;
        int userscore = 0, compscore = 0;
        double size;  

        System.Windows.Forms.Timer botdelay = new System.Windows.Forms.Timer();
        System.Windows.Forms.Timer botdelayfinished = new System.Windows.Forms.Timer();
        System.Windows.Forms.Timer whofirstdelay = new System.Windows.Forms.Timer();

        //rowSequence keeps track of the rows being selected later on.
        List<int> rowSequence = new List<int>();
        List<int> amountSequence = new List<int>();
        List<int> columnSequence = new List<int>();

        public MainWindow()
        {
            InitializeComponent();
            StartGame();
            botdelay.Enabled = false;
            botdelayfinished.Enabled = false;
            botdelay.Interval = 1500;
            botdelayfinished.Interval = 1500;
            whofirstdelay.Interval = 2500;

            botdelay.Tick += new EventHandler(botdelay_Tick);
            botdelayfinished.Tick += new EventHandler(botdelayfinished_Tick);
            whofirstdelay.Tick += new EventHandler(whofirstdelay_Tick);
        }

        public void StartGame()
        {
            //Establish the random amount of rows and columns.
            Random number = new Random();

            //Random generated value used for how many rows will be in a game.
            rows_amount = number.Next(rows - 2) + 3;

            //Establish the amount of elements in each row.
            for (int i = 0; i < (rows_amount); i++)
            {
                columnSequence.Add(number.Next(columns) + 1);
            }

            //Establish the amount of elements in each row.
            for (int i = 0; i < (rows_amount); i++)
            {
                amountSequence.Add(columnSequence[i]);
            }

            //List used to track of which row the element is in.
            for (int i = 0; i < rows_amount; i++)
            {
                //Variable created to keep track of how many elements are in the row being tested.
                int amountInRow = columnSequence[i];
                for (int j = 0; j < amountInRow; j++)
                {
                    //LOGIC: Each element is assigned to a spot in this list (0th spot being the first element(item),
                    //and so on). The number assigned to them is the row they are in.
                    rowSequence.Add(i);
                }
            }

            //Variable columnsmax used to find the max amount of elements in a row.
            //This is used for spacing the items in the game to be the same in each row.
            int columnsmax = 0;
            for (int r = 0; r < rows_amount; r++)
            {
                if (columnsmax < columnSequence[r])
                    columnsmax = columnSequence[r];
            }

            //Size variable used to find the correct size of the elements used.
            size = 10 + canvas1.Height / (rows_amount + 1) / 10 + canvas1.Width / (columnsmax + 1) / 10;

            //Counter variable used for next for statement:
            int itick = 0;

            //Establishes the y spacing between each element.
            float dy = (float)canvas1.Height / (rows_amount + 1.0F);
            for (int r = 0; r < rows_amount; r++)
            {
                float dx = ((float)canvas1.Width - (float)(columnsmax * size)) / (columnsmax + 1);
                for (int c = 0; c < columnSequence[itick]; c++)
                {
                    //Create a fresh ellipse.
                    Ellipse newEllipse = new Ellipse();
                    Point position = new Point();
                    double x, y = 0;

                    //Color it, and give it a size.
                    newEllipse.Fill = Brushes.Red;     
                    newEllipse.Width = size;
                    newEllipse.Height = size;

                    //X and Y are determined by the size of the elements as well as how many
                    //rows and columns are in the current game.
                    x = (dx + c * dx + size * c);
                    y = (dy + r * dy);
                    position = new Point(x, y);

                    //Set the position of the ellipse.
                    Canvas.SetTop(newEllipse, position.Y);
                    Canvas.SetLeft(newEllipse, position.X);

                    //Add the new ellipse to the canvas.
                    canvas1.Children.Add(newEllipse);
                }
                itick++;
            }
            whofirstdelay.Start();
        }

        //Event for Clicking New Game on the Menu Strip.
        private void MenuItem_Click(object sender, RoutedEventArgs e)
        {
            //Clear canvas1 and columnSequence for a fresh game.
            canvas1.Children.Clear();
            columnSequence.Clear();
            amountSequence.Clear();
            rowSequence.Clear();
            botdelayfinished.Stop();
            botdelay.Stop();
            whofirstdelay.Stop();

            //Clear any selection from memory.
            rowselected = -1;
            amountselected = 0;
            amountneedselected = 0;
            correctrow = 0;
            botflag = 0;
            startflag = 1;

            //Hide text
            border1.Visibility = Visibility.Hidden;
            textBlock.Text = "";

            //Start the game again.
            StartGame();
        }

        //Event for Clicking Set MAX Rows and Columns on the Menu Strip.
        private void MenuItem_Click_1(object sender, RoutedEventArgs e)
        {
            //Show the form to change rows/columns
            SetRowsColumns Form2 = new SetRowsColumns();
            Form2.ShowDialog();

            //If the DiaglogResult is true (from pressing OK) then proceed.
            if (Form2.DialogResult == true)
            {
                //Assign the values entered to columns and rows.
                columns = Form2.column;
                rows = Form2.row;
            }
        }

        //Event for clicking the left mouse button down over the canvas.
        private void canvas1_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            if (botflag != 1 && startflag != 1)
            {
                for (int i = 0; i < canvas1.Children.Count; i++)
                {//test to see if the mouse is over an element.
                    if ((canvas1.Children[i] as Ellipse).IsMouseDirectlyOver)
                    {//test to see if the row selected matches the one already selected, or if no row has been selected.
                        if (rowselected == rowSequence[i] || rowselected == -1)
                        {
                            //Make rowselected equal to the row being selected, if it hasn't been done already.
                            if (rowselected == -1)
                                rowselected = rowSequence[i];

                            //Create a new ellipse called colored to store the element in question.
                            Ellipse colored = new Ellipse();
                            colored = (Ellipse)canvas1.Children[i];

                            //If the selected element isn't selected yet, select it.
                            if (colored.Fill == Brushes.Red)
                            {
                                colored.Fill = Brushes.Green;
                                canvas1.Children[i] = colored;
                                //incremement amountselected because one more element has been selected.
                                amountselected++;
                            }
                            //Else if, the element is selected, then unselect it.
                            else if (colored.Fill == Brushes.Green)
                            {
                                colored.Fill = Brushes.Red;
                                canvas1.Children[i] = colored;
                                //decrement amountselected because one more element has been unselected.
                                amountselected--;
                            }
                            //Do nothing if the token is deleted.
                            else if (colored.Fill == canvas1.Background)
                            { }

                            //If the user unselects all element in a row, the user may go to another row.
                            if (amountselected == 0)
                            {
                                //A value of -1 means that no row is currently selected.
                                rowselected = -1;
                            }
                        }
                        //If the row being selected isn't the same that has already been selected, then give error.
                        else if (rowselected != rowSequence[i])
                        {
                            MessageBox.Show("Error: You can't choose from multiple rows.");
                        }
                    }
                }
            }
        }

        private void canvas1_MouseRightButtonDown(object sender, MouseButtonEventArgs e)
        {//if no tokens are selected, give an error.
            //for (int i = 0; i < rows_amount; i++)
            //    Console.WriteLine("Row {0} = {1}", i, amountSequence[i]);
            if (botflag != 1 && startflag != 1)
            {
                if (amountselected == 0)
                    MessageBox.Show("Error: You must choose at least 1 token.");
                else
                {//subtract the amount selected from how many are in the row.
                    amountSequence[rowselected] -= amountselected;

                    //No more tokens are selected.
                    amountselected = 0;
                    //User free to choose from a new row now.
                    rowselected = -1;

                    foreach (Ellipse ellipse in canvas1.Children)
                    {
                        if (ellipse.Fill == Brushes.Green)
                        {//"delete" token by hiding it.
                            ellipse.Fill = canvas1.Background;
                        }
                    }

                    int seeifend = 0;
                    for (int i = 0; i < rows_amount; i++)
                    {
                        seeifend += amountSequence[i];
                    }
                    if (seeifend == 0)
                        gameover(0);
                    else
                        bot_turn();
                }
            }
        }

        public void bot_turn()
        {//value used to store the xorvalue of the tokens for the bot to analyze.
            int xorvalue = 0;
            botflag = 1;

            //binary value of the xor value.
            int[] bytevalue = new int[8];
            //binary value of the rows being tested.
            int[] bytevalue2 = new int[8];

            //for statement gets the xorvalue of the rows.
            for (int i = 0; i < rows_amount; i++)
                    xorvalue ^= amountSequence[i];

            for (int i = 0; i < 8; i++)
            {
                bytevalue[i] = 0;
            }
            for (int i = 0; i < 8; i++)
            {
                bytevalue2[i] = 0;
            }

            if (xorvalue != 0)
            {
                //Variable used to find the highest variable that is 1.
                int powerof2 = 0;
                int one_placement = -1;
                int comp_position = 7;

                //gets the binary value of the xorvalue.
                while (xorvalue != 0)
                {
                    one_placement = -1;
                    for (int i = 1; i <= xorvalue; i *= 2)
                    {
                        one_placement++;
                        powerof2 = i;
                    }
                    xorvalue -= powerof2;
                    if (comp_position > (7 - one_placement))
                        comp_position = 7 - one_placement;
                    bytevalue[7 - one_placement] = 1;
                }

                //gets the binary of each row, and checks to see if comp_position matches theirs
                for (int i = 0; i < rows_amount; i++)
                {
                    int amount_without_alter = amountSequence[i];

                    for (int k = 0; k < 8; k++)
                    {
                        bytevalue2[k] = 0;
                    }

                    while (amount_without_alter != 0)
                    {
                        one_placement = -1;
                        for (int j = 1; j <= amount_without_alter; j *= 2)
                        {
                            one_placement++;
                            powerof2 = j;
                        }
                        amount_without_alter -= powerof2;
                        bytevalue2[7 - one_placement] = 1;
                    }

                    if (bytevalue2[comp_position] == 1)
                    {
                        correctrow = i;
                        i = rows_amount;
                    }
                }

                //Converts the row that is in binary to what it will be once
                //the correct amount of items are deleted.
                for (int i = 0; i < 8; i++)
                {
                    if (bytevalue[i] == 1)
                    {
                        if (bytevalue2[i] == 1)
                            bytevalue2[i] = 0;
                        else
                            bytevalue2[i] = 1;
                    }
                }
                //Valueholder is the int value of the row after selections
                int valueholder = 0;
                int tick = 0;
                for (int i = 1; i < Math.Pow(2, comp_position); i *= 2)
                {
                    valueholder += bytevalue2[7 - tick] * i;
                    tick++;
                }

                //Amount that needs to be selected.
                amountneedselected = amountSequence[correctrow] - valueholder;

                //Enable timer to have delay so user see what bot does.
                botdelay.Start();
            }
            else
            {
                Random random = new Random();
                correctrow = -1;
                int storedvalue;

                for (int i = 0; correctrow == -1; i++)
                {
                    storedvalue = random.Next(rows_amount);
                    if (amountSequence[storedvalue] != 0)
                        correctrow = storedvalue;
                }

                amountneedselected = (random.Next(amountSequence[correctrow]) + 1);

                botdelay.Start();
            }
        }

        //Delay timer for the bot to show what he does.
        private void botdelay_Tick(object sender, EventArgs e)
        {
            int itick = 0;

            //Selects the amount of items needed to finish the bots turn.
            for (int i = 0; i < amountneedselected; i++)
            {
                int testflag = 0;
                while (testflag == 0)
                {
                    if (rowSequence[itick] == correctrow)
                    {
                        Ellipse colored = new Ellipse();
                        colored = (Ellipse)canvas1.Children[itick];

                        if (colored.Fill != canvas1.Background)
                        {
                            colored.Fill = Brushes.Green;
                            canvas1.Children[itick] = colored;
                            testflag = 1;
                        }
                    }
                    itick++;
                }
            }

            //Subtract the amount from the stored value.
            amountSequence[correctrow] -= amountneedselected;
            amountneedselected = 0;
            correctrow = 0;

            //Start the second timer to finish up the bots turn, erasing the selected items.
            botdelayfinished.Start();
            botdelay.Stop();
        }

        //Delay timer to show the bot deleting his selections.
        private void botdelayfinished_Tick(object sender, EventArgs e)
        {
            foreach (Ellipse ellipse in canvas1.Children)
            {
                if (ellipse.Fill == Brushes.Green)
                    ellipse.Fill = canvas1.Background;
            }
            botflag = 0;
            startflag = 0;

            int seeifend = 0;
            for (int i = 0; i < rows_amount; i++)
            {
                seeifend += amountSequence[i];
            }
            if (seeifend == 0)
                gameover(1);
            botdelayfinished.Stop();
        }

        //Method to figure out scores.
        public void gameover(int x)
        {
            //A 1 will be sent if the comp finishes first.
            if (x == 1)
                compscore++;
            //A 0 will be sent if the user finishes first.
            else
                userscore++;

            displayscore();
        }

        //Instruction event for when the "Instruction" Menu option is clicked.
        private void instructionsToolStripMenuItem_Click(object sender, RoutedEventArgs e)
        {
            string aboutstring =
                    @"  Welcome to the game of Nim!
    
                        The point of the game is to be the last one to draw tokens.

                        You are allowed to draw from any row, but are only allowed
                        to draw from the same row. You also must select at least
                        one token. Tokens are represented as red circles.
            
                        The game will start, then ask to see if you want to go first
                        or not. Xing out of the box or clicking No will make the bot
                        go first. Clicking yes will allow you to go first.

                        You may not go during a bot's turn.
        
                        Left clicking on a token will select it, while right clicking
                        the form will end your turn, and any tokens selected will be
                        deleted from the board.

                        Good luck!";

            MessageBox.Show(aboutstring);
        }

        //Displays the score to the user once the game is over.
        public void displayscore()
        {
            canvas1.Children.Clear();
            string scoretext =
                @"score
Me: " + compscore + @"
You: " + userscore;
            border1.Visibility = Visibility.Visible;
            textBlock.Text = scoretext;
        }

        public void showwhofirst()
        {
            whofirstdelay.Stop();
            WhoFirst Form3 = new WhoFirst();
            Form3.ShowDialog();

            //If the DiaglogResult is false, then bot goes first.
            if (Form3.DialogResult == false)
            {
                bot_turn();
            }
            else
                startflag = 0;
        }

        //Method to decide who goes first in the program. The timer tick.
        private void whofirstdelay_Tick(object sender, EventArgs e)
        {
            showwhofirst();
        }
    }
}
