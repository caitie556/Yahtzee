/*
* Name: Caitlin Cunningham
* Class: CptS 121, Andrew O'Fallon
* Description: PA5 - Develope and implement a two-player Yahtzee game
*/

#include "yahtzee.h"

int main(void)
{
	srand(time(0));
	int menu = 0;

	menu = get_menu_choice(); //displays menu to user and gets option
	while (menu != 3)
	{
		if (menu == 1)//display rules option
		{
			printf("The scorecard used for Yahtzee is composed of two sections. A upper section and a lower section.\nA total of thirteen boxes or thirteen scoring combinations are divided amongst the sections.\nThe upper section consists of boxes that are scored by summing the value of the dice matching the faces of the box.\nIf a player rolls four 3's, then the score placed in the 3's box is the sum of the dice which is 12.\nOnce a player has chosen to score a box, it may not be changed and the combination is no longer in play for future rounds.\nIf the sum of the scores in the upper section is greater than or equal to 63, then 35 more points are added to the players overall score as a bonus.\nThe lower section contains a number of poker like combinations.\n\n");
			menu = get_menu_choice();
		}
		else if (menu == 2) //start game option
		{
			int round = 0, p1_score = 0, p2_score = 0, sum = 0, rolls = 0, reroll = 0, player = 1;
			int p1_combos[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
			int p2_combos[13] = { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 };
			int dice[5] = { 0 };
			char c = '\0';

			while(round < 14) //alternates players -> player1 = 1 and player2 = -1
			{
				if (player == 1)
				{
					printf("Player 1's turn\n");
				}
				else if (player == -1)
				{
					printf("Player 2's turn\n");
				}

				roll_dice(dice);
				rolls++;

				printf("Would you like to use this roll for a combination?\n");
				scanf(" %c", &c);
				if (c == 'y' || c == 'Y') //use combo
				{
					sum = sum_array(dice, 5);
					if (player == 1)
					{
						use_combination(p1_combos, sum);
					}
					else if (player == -1)
					{
						use_combination(p2_combos, sum);
					}
					
				}
				else //ask for reroll up to two more times
				{
					do
					{
						reroll = reroll_dice(dice);
						if (reroll == 1)
						{
							rolls++;
						}
					} while (reroll != 0 && rolls != 3); //if user says no the first time, doesnt ask a second time

					sum = sum_array(dice, 5); //user must use combination at this point
					if (player == 1) //player 1
					{
						use_combination(p1_combos, sum);
					}
					else if (player == -1) //player 2
					{
						use_combination(p2_combos, sum);
					}
				}//end of turn

				if (player == -1) //adds to round after player 2's turn
				{
					round++;
				}
				player = player * -1;
				system("cls");
			}

			system("cls");
			//calculates scores and determines winner when round = 14
			p1_score = sum_array(p1_combos, 13);
			p2_score = sum_array(p2_combos, 13);

			if (sum_array(p1_combos, 6) >= 63)
			{
				p1_score += 35;
			}
			if (sum_array(p2_combos, 6) >= 63)
			{
				p2_score += 35;
			}
			printf("Player 1: %d\nPlayer 2: %d\n", p1_score, p2_score);

			if (p1_score > p2_score) //player 1 score is greater than player 2 score
			{
				printf("Player 1 wins!");
			}
			else if (p2_score > p1_score)//player 2 score is greater than player 1 score
			{
				printf("Player 2 wins!");
			}
			else
			{
				printf("Both Players Tied!");
			}

			menu = get_menu_choice(); //displays menu after game ends
			system("cls");
		}
	}

	return 0;
}