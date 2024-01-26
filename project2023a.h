#include <stdio.h>

struct hand {
  char cards[13][4];
};

int readFromInput(struct hand A[]) {
  int n, p1, p2, p3, p4;
  char ch1, ch2;
  scanf("%d", &n);

  for (int i = 0; i < n; i++) {
    p1 = 0;
    p2 = 0;
    p3 = 0;
    p4 = 0;

    for (int j = 0; j < 13; j++) {
      scanf(" %c%c ", &ch1, &ch2);

      switch (ch2) {
      case 'S': // spades
        A[i].cards[p1][0] = ch1;
        p1++;
        break;
      case 'H': // hearts
        A[i].cards[p2][1] = ch1;
        p2++;
        break;
      case 'D': // diamonds
        A[i].cards[p3][2] = ch1;
        p3++;
        break;
      case 'C': // clubs
        A[i].cards[p4][3] = ch1;
        p4++;
        break;
      }
    }
  }
  return n;
}

void printHand(struct hand A) {
  for (int i = 0; i < 4; i++) {
    printf("%s ", (i == 0)   ? "SPADES:  "
                  : (i == 1) ? "HEARTS:  "
                  : (i == 2) ? "DIAMONDS:"
                             : "CLUBS:   ");

    for (int j = 0; j < 13 && A.cards[j][i] != '\0'; j++)
      printf("%c ", A.cards[j][i]);

    printf("\n");
  }
}

int declarer(struct hand A) {
  int points = 0, spades = 0, hearts = 0, diamonds = 0, clubs = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13 && A.cards[j][i] != '\0'; j++) {
      if (i == 0)
        spades++;
      else if (i == 1)
        hearts++;
      else if (i == 2)
        diamonds++;
      else
        clubs++;
    }
  }

  if (spades > 4)
    points += (spades - 4);
  if (hearts > 4)
    points += (hearts - 4);
  if (diamonds > 4)
    points += (diamonds - 4);
  if (clubs > 4)
    points += (clubs - 4);

  return points;
}

int hcp(struct hand A) {
  int points = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13 && A.cards[j][i] != '\0'; j++) {
      switch (A.cards[j][i]) {
      case 'A':
        points += 4;
        break;
      case 'K':
        points += 3;
        break;
      case 'Q':
        points += 2;
        break;
      case 'J':
        points += 1;
        break;
      }
    }
  }

  return points;
}

bool balanced(struct hand A) {
  bool isBalanced = false;
  int spades = 0, hearts = 0, diamonds = 0, clubs = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13 && A.cards[j][i] != '\0'; j++) {
      if (i == 0)
        spades++;
      else if (i == 1)
        hearts++;
      else if (i == 2)
        diamonds++;
      else
        clubs++;
    }
  }

  if (spades > 1 && hearts > 1 && diamonds > 1 && clubs > 1) {
    isBalanced = true;

    if (spades == 2) {
      if (hearts == 2 || diamonds == 2 || clubs == 2)
        isBalanced = false;
    }

    if (hearts == 2) {
      if (diamonds == 2 || clubs == 2 || spades == 2)
        isBalanced = false;
    }

    if (diamonds == 2) {
      if (clubs == 2 || spades == 2 || hearts == 2)
        isBalanced = false;
    }
  }

  return isBalanced;
}

void response(struct hand A) {
  bool isBalanced = balanced(A);
  int hcPoints = hcp(A);
  int decPoints = declarer(A);

  int spades = 0, hearts = 0, diamonds = 0, clubs = 0;

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 13 && A.cards[j][i] != '\0'; j++) {
      if (i == 0)
        spades++;
      else if (i == 1)
        hearts++;
      else if (i == 2)
        diamonds++;
      else
        clubs++;
    }
  }

  if (isBalanced && hcPoints > 14 && hcPoints < 18)
    printf("1NT\n");
  else if (isBalanced && hcPoints > 19 && hcPoints < 22)
    printf("2NT\n");
  else if (hcPoints > 21)
    printf("2 CLUBS\n");
  else if (hcPoints + decPoints > 12) {
    if (spades >= 5 && hearts < 5)
      printf("1 SPADES\n");
    else if (hearts >= 5 && spades < hearts)
      printf("1 HEARTS\n");
    else if (diamonds > 3 && spades < 5 && hearts < 5 && clubs <= 4)
      printf("1 DIAMONDS\n");
    else if (spades <= 4 && hearts < 5 && diamonds < 4)
      printf("1 CLUBS\n");
  } else if (hcPoints + decPoints < 13)
    printf("PASS\n");
}

int readFromFile(struct hand A[]) {
  char ch1, ch2, error = 0;
  char txt[30];
  int n, p1, p2, p3, p4;

  scanf("%29s", &txt[0]);

  FILE *fp = fopen(txt, "r");

  if (fp != NULL) {
    while (!feof(fp) && !error) {
      fscanf(fp, "%d", &n);

      for (int i = 0; i < n; i++) {
        p1 = 0;
        p2 = 0;
        p3 = 0;
        p4 = 0;

        for (int j = 0; j < 13; j++) {
          fscanf(fp, " %c%c ", &ch1, &ch2);

          switch (ch2) {
          case 'S': // spades
            A[i].cards[p1][0] = ch1;
            p1++;
            break;
          case 'H': // hearts
            A[i].cards[p2][1] = ch1;
            p2++;
            break;
          case 'D': // diamonds
            A[i].cards[p3][2] = ch1;
            p3++;
            break;
          case 'C': // clubs
            A[i].cards[p4][3] = ch1;
            p4++;
            break;
          }
        }
      }
    }
    fclose(fp);
  }
  return n;
}

void saveData(struct hand A[], int n) {
  char txt[30];

  scanf("%29s", txt);

  FILE *fp = fopen(txt, "w");

  if (fp != NULL) {
    for (int k = 0; k < n; k++) {
      for (int i = 0; i < 4; i++) {
        fprintf(fp, "%s ",
                (i == 0)   ? "SPADES:  "
                : (i == 1) ? "HEARTS:  "
                : (i == 2) ? "DIAMONDS:"
                           : "CLUBS:   ");

        for (int j = 0; j < 13 && A[k].cards[j][i] != '\0'; j++) {
          if (i == 0)
            fprintf(fp, "%c ", A[k].cards[j][0]);
          else if (i == 1)
            fprintf(fp, "%c ", A[k].cards[j][1]);
          else if (i == 2)
            fprintf(fp, "%c ", A[k].cards[j][2]);
          else if (i == 3)
            fprintf(fp, "%c ", A[k].cards[j][3]);
        }
        fputs("\n", fp);
      }
      fputs("\n", fp);
    }
  }
}