#include "yahtzee.h"

int get_menu_choice(void)
{
	int choice = 0;
	printf("Select Menu option: \n");
	do
	{
		printf("1. Print game rules\n2. Start game of Yahtzee\n3. Exit\n");
		scanf("%d", &choice);
	} while (choice < 0 && choice > 3);

	system("cls");

	return choice;
}

void roll_dice(int dice[5])
{
	printf("Roll dice\n");
	system("pause");

	for (int index = 0; index < 5; index++)
	{
		dice[index] = rand() % 6 + 1;
		printf("die%d: %d ", index+1, dice[index]);
	}
	printf("\n");
}

int reroll_dice(int dice[5])
{
	char c = '\0';
	int reroll = 0;
	printf("Would you like to reroll any dice? (y/n)\n");
	scanf(" %c", &c);
	if (c == 'y' || c == 'Y')
	{
		for (int index = 0; index < 5; index++)
		{
			//c = '\0';
			printf("Would you like to reroll die%d? (y/n)\n", index + 1);
			scanf(" %c", &c);
			if (c == 'y' || c == 'Y')
			{
				dice[index] = rand() % 6 + 1;
				reroll = 1;
			}
		}
		system("cls");

		for (int index = 0; index < 5; index++)
		{
			printf("die%d: %d ", index + 1, dice[index]);
		}

	}

	return reroll;
}

int sum_array(int a[], int size)
{
	int sum = 0;

	for (int index = 0; index < size; index++)
	{
		sum += a[index];
	}

	return sum;
}

void use_combination(int points[13], int dice[5], int sum)
{
	int combo = -1, num = 0;
	printf("which combination would you like to use?\n");
	printf("1. Sum of 1's\n2. Sum of 2's\n3. Sum of 3's\n4. Sum of 4's\n5. Sum of 5's\n6.Sum of 6's\n7. Three-of-a-kind\n8. Four-of-a-kind\n9. Full house\n10. Small straight\n11. Large straight\n12. Yahtzee\n13.Chance\n");
	scanf(" %d", &combo);
	combo = combo - 1;

	while(points[combo] > -1) //checks to see if element is already used i.e not at the initial value
	{
		printf("Choose a different combination\n");
		scanf(" %d", &combo);
		combo = combo - 1;
	}
	
	if (points[combo] == -1)
	{
		if (combo == 0) //sum of 1's
		{
			for (int index = 0; index < 5; index++)
			{
				if (points[index] == 1)
				{
					num++;
				}
			}
			points[combo] = num;
		}
		else if (combo == 1)//sum of 2's
		{
			for (int index = 0; index < 5; index++)
			{
				if (points[index] == 2)
				{
					num += 2;
				}
			}
			points[combo] = num;
		}
		else if (combo == 2)//sum of 3's
		{
			for (int index = 0; index < 5; index++)
			{
				if (points[index] == 3)
				{
					num += 3;
				}
			}
			points[combo] = num;
		}
		else if (combo == 3)//sum of 4's
		{
			for (int index = 0; index < 5; index++)
			{
				if (points[index] == 4)
				{
					num += 4;
				}
			}
			points[combo] = num;
		}
		else if (combo == 4)//sum of 5's
		{
			for (int index = 0; index < 5; index++)
			{
				if (points[index] == 5)
				{
					num += 5;
				}
			}
			points[combo] = num;
		}
		else if (combo == 5)//sum of 6's
		{
			for (int index = 0; index < 5; index++)
			{
				if (points[index] == 6)
				{
					num += 6;
				}
			}
			points[combo] = num;
		}
		else if (combo == 6)//Three of a kind
		{
			for (int index = 0; index < 5; index++)//goes through the dice array
			{
				for (int i = index + 1; i < 5; i++)//the next value in the array
				{
					if (dice[index] == dice[i]) //compares initial value to current value
					{
						num++; //counts how many times, that value appears
						if (num == 2) //once a value is found 2 more times, add sum to points[combo]
						{
							points[combo] = sum;
						}
					}

				}
				num = 0;
			}

			if (points[combo] == -1)
			{
				points[combo] = 0;
			}
			
		}
		else if (combo == 7)//Four of a kind
		{
			for (int index = 0; index < 5; index++)//goes through the dice array
			{
				for (int i = index + 1; i < 5; i++)//the next value in the array
				{
					if (dice[index] == dice[i]) //compares initial value to current value
					{
						num++; //counts how many times, that value appears
						if (num == 3) //once a value is found 3 more times, add sum to points[combo]
						{
							points[combo] = sum;
						}
					}

				}
				num = 0;
			}
			if (points[combo] == -1)
			{
				points[combo] = 0;
			}
		}
		else if (combo == 8)//Full house
		{
			int found3 = 0, found2 = 0;
			for (int index = 0; index < 5; index++)//goes through the dice array
			{
				for (int i = index + 1; i < 5; i++)//the next value in the array
				{
					if (dice[index] == dice[i]) //compares initial value to current value
					{
						num++; //counts how many times, that value appears
						if (num == 2) //once a value is found 2 more times
						{
							found3 = 1;
						}
					}

				}
				num = 0;

				for (int i = index + 1; i < 5; i++)//the next value in the array
				{
					if (dice[index] == dice[i]) //compares initial value to current value
					{
						num++; //counts how many times, that value appears
						if (num == 1) //once a value is found again
						{
							found2 = 1;
						}
					}

				}
				num = 0;
			}
			if (found2 && found3)
			{
				points[combo] = 25;
			}
		}
		else if (combo == 9)//Small straight
		{
		int in_a_row = 0, last = 0;
			for (int index = 0; index < 5; index++) //iterates through array
			{
				last = dice[index];
				for (int i = 0; i < 5; i++) //finds the next value
				{
					if (dice[i] == last + 1 && in_a_row != 3)
					{
						in_a_row++;
						last = dice[i];
					}
				}
			}
			if (in_a_row == 3)
			{
				points[combo] = 30;
			}
			else
			{
				points[combo] = 0;
			}
		}
		else if (combo == 10)//Large straight
		{
		int in_a_row = 0, last = 0;
		for (int index = 0; index < 5; index++) //iterates through array
		{
			last = dice[index];
			for (int i = 0; i < 5; i++) //finds the next value
			{
				if (dice[i] == last + 1 && in_a_row != 5)
				{
					in_a_row++;
					last = dice[i];
				}
			}
		}
		if (in_a_row == 5)
		{
			points[combo] = 40;
		}
		else
		{
			points[combo] = 0;
		}
		}
		else if (combo == 11)//Yahtzee
		{
			for (int index = 0; index < 5; index++)//goes through the dice array
			{
				for (int i = index + 1; i < 5; i++)//the next value in the array
				{
					if (dice[index] == dice[i]) //compares initial value to current value
					{
						num++; //counts how many times, that value appears
						if (num == 4) //once a value is found 4 more times, add 50 to points[combo]
						{
							points[combo] = 50;
						}
					}

				}
				num = 0;
			}
		}
		else if (combo == 12)//Chance
		{
			points[combo] = sum;
		}
	}
}