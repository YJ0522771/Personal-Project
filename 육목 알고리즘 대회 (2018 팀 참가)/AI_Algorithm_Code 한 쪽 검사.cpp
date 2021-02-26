// Samsung Go Tournament Form C (g++-4.8.3)

/*
[AI 코드 작성 방법]

1. char info[]의 배열 안에					"TeamName:자신의 팀명,Department:자신의 소속"					순서로 작성합니다.
( 주의 ) Teamname:과 Department:는 꼭 들어가야 합니다.
"자신의 팀명", "자신의 소속"을 수정해야 합니다.

2. 아래의 myturn() 함수 안에 자신만의 AI 코드를 작성합니다.

3. AI 파일을 테스트 하실 때는 "육목 알고리즘대회 툴"을 사용합니다.

4. 육목 알고리즘 대회 툴의 연습하기에서 바둑돌을 누른 후, 자신의 "팀명" 이 들어간 알고리즘을 추가하여 테스트 합니다.



[변수 및 함수]
myturn(int cnt) : 자신의 AI 코드를 작성하는 메인 함수 입니다.
int cnt (myturn()함수의 파라미터) : 돌을 몇 수 둬야하는지 정하는 변수, cnt가 1이면 육목 시작 시  한 번만  두는 상황(한 번), cnt가 2이면 그 이후 돌을 두는 상황(두 번)
int  x[0], y[0] : 자신이 둘 첫 번 째 돌의 x좌표 , y좌표가 저장되어야 합니다.
int  x[1], y[1] : 자신이 둘 두 번 째 돌의 x좌표 , y좌표가 저장되어야 합니다.
void domymove(int x[], int y[], cnt) : 둘 돌들의 좌표를 저장해서 출력


//int board[BOARD_SIZE][BOARD_SIZE]; 바둑판 현재상황 담고 있어 바로사용 가능함. 단, 원본데이터로 수정 절대금지
// 놓을수 없는 위치에 바둑돌을 놓으면 실격패 처리.

boolean ifFree(int x, int y) : 현재 [x,y]좌표에 바둑돌이 있는지 확인하는 함수 (없으면 true, 있으면 false)
int myBoard(x[0], y[0], count, int x, int y) : [x, y] 좌표에 무슨 돌이 존재하는지 보여주는 함수 (1 = 자신의 돌, 2 = 상대의 돌, 3 = 블럭킹)


<-------AI를 작성하실 때, 같은 이름의 함수 및 변수 사용을 권장하지 않습니다----->
*/

#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include "Connect6Algo.h"

// "샘플코드[C]"  -> 자신의 팀명 (수정)
// "AI부서[C]"  -> 자신의 소속 (수정)
// 제출시 실행파일은 반드시 팀명으로 제출!
char info[] = { "TeamName:생크림케이크,Department:경북대학교" };

int AWin_case(int s[6]);
int Arr_Equal(int s[6], int p[6]);
int is_OK(int my_x, int my_y, int count, int x, int y);
int Max(int a, int b);
int Min(int a, int b);
int myBoard(int my_x, int my_y, int count, int x, int y);
int Cross_4(int x, int y);

int yeo5(int x, int y, int case_state, int * r_x, int * r_y)
{
	switch (case_state)
	{
	case 111:
		if (is_OK(x + 3, y, 1, x + 1, y) && is_OK(x + 1, y, 1, x + 3, y))
		{
			r_x[0] = x + 1;
			r_y[0] = y;
			r_x[1] = x + 3;
			r_y[1] = y;
			return 1;
		}
		break;
	case 211:
		if (is_OK(x, y + 1, 1, x, y + 3) && is_OK(x, y + 3, 1, x, y + 1))
		{
			r_x[0] = x;
			r_y[0] = y + 1;
			r_x[1] = x;
			r_y[1] = y + 3;
			return 1;
		}
		break;
	case 311:
		if (is_OK(x + 1, y + 1, 1, x + 3, y + 3) && is_OK(x + 3, y + 3, 1, x + 1, y + 1))
		{
			r_x[0] = x + 1;
			r_y[0] = y + 1;
			r_x[1] = x + 3;
			r_y[1] = y + 3;
			return 1;
		}
		break;
	case 411:
		if (is_OK(x - 1, y + 1, 1, x - 3, y + 3) && is_OK(x - 3, y + 3, 1, x - 1, y + 1))
		{
			r_x[0] = x - 1;
			r_y[0] = y + 1;
			r_x[1] = x - 3;
			r_y[1] = y + 3;
			return 1;
		}
		break;
		//11
	case 112:
		if (is_OK(x + 4, y, 1, x + 2, y) && is_OK(x + 2, y, 1, x + 4, y))
		{
			r_x[0] = x + 2;
			r_y[0] = y;
			r_x[1] = x + 4;
			r_y[1] = y;
			return 1;
		}
		break;
	case 212:
		if (is_OK(x, y + 2, 1, x, y + 4) && is_OK(x, y + 4, 1, x, y + 2))
		{
			r_x[0] = x;
			r_y[0] = y + 2;
			r_x[1] = x;
			r_y[1] = y + 4;
			return 1;
		}
		break;
	case 312:
		if (is_OK(x + 2, y + 2, 1, x + 4, y + 4) && is_OK(x + 4, y + 4, 1, x + 2, y + 2))
		{
			r_x[0] = x + 2;
			r_y[0] = y + 2;
			r_x[1] = x + 4;
			r_y[1] = y + 4;
			return 1;
		}
		break;
	case 412:
		if (is_OK(x - 2, y + 2, 1, x - 4, y + 4) && is_OK(x - 4, y + 4, 1, x - 2, y + 2))
		{
			r_x[0] = x - 2;
			r_y[0] = y + 2;
			r_x[1] = x - 4;
			r_y[1] = y + 4;
			return 1;
		}
		break;
		//12
	case 113:
		if (is_OK(x + 1, y, 1, x + 2, y) && is_OK(x + 2, y, 1, x + 1, y))
		{
			r_x[0] = x + 2;
			r_y[0] = y;
			r_x[1] = x + 1;
			r_y[1] = y;
			return 1;
		}
		break;
	case 213:
		if (is_OK(x, y + 2, 1, x, y + 1) && is_OK(x, y + 1, 1, x, y + 2))
		{
			r_x[0] = x;
			r_y[0] = y + 2;
			r_x[1] = x;
			r_y[1] = y + 1;
			return 1;
		}
		break;
	case 313:
		if (is_OK(x + 2, y + 2, 1, x + 1, y + 1) && is_OK(x + 1, y + 1, 1, x + 2, y + 2))
		{
			r_x[0] = x + 2;
			r_y[0] = y + 2;
			r_x[1] = x + 1;
			r_y[1] = y + 1;
			return 1;
		}
		break;
	case 413:
		if (is_OK(x - 2, y + 2, 1, x - 1, y + 1) && is_OK(x - 1, y + 1, 1, x - 2, y + 2))
		{
			r_x[0] = x - 2;
			r_y[0] = y + 2;
			r_x[1] = x - 1;
			r_y[1] = y + 1;
			return 1;
		}
		break;
		//13
	case 114:
		if (is_OK(x + 3, y, 1, x + 2, y) && is_OK(x + 2, y, 1, x + 3, y))
		{
			r_x[0] = x + 2;
			r_y[0] = y;
			r_x[1] = x + 3;
			r_y[1] = y;
			return 1;
		}
		break;
	case 214:
		if (is_OK(x, y + 2, 1, x, y + 3) && is_OK(x, y + 3, 1, x, y + 2))
		{
			r_x[0] = x;
			r_y[0] = y + 2;
			r_x[1] = x;
			r_y[1] = y + 3;
			return 1;
		}
		break;
	case 314:
		if (is_OK(x + 2, y + 2, 1, x + 3, y + 3) && is_OK(x + 3, y + 3, 1, x + 2, y + 2))
		{
			r_x[0] = x + 2;
			r_y[0] = y + 2;
			r_x[1] = x + 3;
			r_y[1] = y + 3;
			return 1;
		}
		break;
	case 414:
		if (is_OK(x - 2, y + 2, 1, x - 3, y + 3) && is_OK(x - 3, y + 3, 1, x - 2, y + 2))
		{
			r_x[0] = x - 2;
			r_y[0] = y + 2;
			r_x[1] = x - 3;
			r_y[1] = y + 3;
			return 1;
		}
		break;
		//14
	case 116:
		if (is_OK(x + 3, y, 1, x + 2, y) && is_OK(x + 2, y, 1, x + 3, y))
		{
			r_x[0] = x + 2;
			r_y[0] = y;
			r_x[1] = x + 3;
			r_y[1] = y;
			return 1;
		}
		break;
	case 216:
		if (is_OK(x, y + 2, 1, x, y + 3) && is_OK(x, y + 3, 1, x, y + 2))
		{
			r_x[0] = x;
			r_y[0] = y + 2;
			r_x[1] = x;
			r_y[1] = y + 3;
			return 1;
		}
		break;
	case 316:
		if (is_OK(x + 2, y + 2, 1, x + 3, y + 3) && is_OK(x + 3, y + 3, 1, x + 2, y + 2))
		{
			r_x[0] = x + 2;
			r_y[0] = y + 2;
			r_x[1] = x + 3;
			r_y[1] = y + 3;
			return 1;
		}
		break;
	case 416:
		if (is_OK(x - 2, y + 2, 1, x - 3, y + 3) && is_OK(x - 3, y + 3, 1, x - 2, y + 2))
		{
			r_x[0] = x - 2;
			r_y[0] = y + 2;
			r_x[1] = x - 3;
			r_y[1] = y + 3;
			return 1;
		}
		break;
		//16
	case 117:
		if (is_OK(x + 4, y, 1, x + 3, y) && is_OK(x + 3, y, 1, x + 4, y))
		{
			r_x[0] = x + 3;
			r_y[0] = y;
			r_x[1] = x + 4;
			r_y[1] = y;
			return 1;
		}
		break;
	case 217:
		if (is_OK(x, y + 3, 1, x, y + 4) && is_OK(x, y + 4, 1, x, y + 3))
		{
			r_x[0] = x;
			r_y[0] = y + 3;
			r_x[1] = x;
			r_y[1] = y + 4;
			return 1;
		}
		break;
	case 317:
		if (is_OK(x + 3, y + 3, 1, x + 4, y + 4) && is_OK(x + 4, y + 4, 1, x + 3, y + 3))
		{
			r_x[0] = x + 3;
			r_y[0] = y + 3;
			r_x[1] = x + 4;
			r_y[1] = y + 4;
			return 1;
		}
		break;
	case 417:
		if (is_OK(x - 3, y + 3, 1, x - 4, y + 4) && is_OK(x - 4, y + 4, 1, x - 3, y + 3))
		{
			r_x[0] = x - 3;
			r_y[0] = y + 3;
			r_x[1] = x - 4;
			r_y[1] = y + 4;
			return 1;
		}
		break;
		//17
	}
	return 0;
}

void weight_handling(int x, int y, int case_state, int weight[19][19][9])
{
	static int linear_weight = 3;//4개가 연속하는 자리일 경우 가산
	int WT;

	if ((case_state % 100) < 21)
		WT = (case_state / 100) - 1;
	else
		WT = (case_state / 100) + 3;
	//weight의 Type

	switch (case_state)
	{
	case 101:
		weight[x + 3][y][WT]++;
		weight[x + 4][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 201:
		weight[x][y + 3][WT]++;
		weight[x][y + 4][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 301:
		weight[x + 3][y + 3][WT]++;
		weight[x + 4][y + 4][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 401:
		weight[x - 3][y + 3][WT]++;
		weight[x - 4][y + 4][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
	//1
	case 102:
		weight[x][y][WT]++;
		weight[x + 4][y][WT] += linear_weight;
		weight[x + 5][y][WT]++;
		break;
	case 202:
		weight[x][y][WT]++;
		weight[x][y + 4][WT] += linear_weight;
		weight[x][y + 5][WT]++;
		break;
	case 302:
		weight[x][y][WT]++;
		weight[x + 4][y + 4][WT] += linear_weight;
		weight[x + 5][y + 5][WT]++;
		break;
	case 402:
		weight[x][y][WT]++;
		weight[x - 4][y + 4][WT] += linear_weight;
		weight[x - 5][y + 5][WT]++;
		break;
		//2
	case 103:
		weight[x][y][WT]++;
		weight[x + 1][y][WT] += linear_weight;
		weight[x + 5][y][WT]++;
		break;
	case 203:
		weight[x][y][WT]++;
		weight[x][y + 1][WT] += linear_weight;
		weight[x][y + 5][WT]++;
		break;
	case 303:
		weight[x][y][WT]++;
		weight[x + 1][y + 1][WT] += linear_weight;
		weight[x + 5][y + 5][WT]++;
		break;
	case 403:
		weight[x][y][WT]++;
		weight[x - 1][y + 1][WT] += linear_weight;
		weight[x - 5][y + 5][WT]++;
		break;
		//3
	case 104:
		weight[x][y][WT]++;
		weight[x + 1][y][WT]++;
		weight[x + 2][y][WT]++;
		break;
	case 204:
		weight[x][y][WT]++;
		weight[x][y + 1][WT]++;
		weight[x][y + 2][WT]++;
		break;
	case 304:
		weight[x][y][WT]++;
		weight[x + 1][y + 1][WT]++;
		weight[x + 2][y + 2][WT]++;
		break;
	case 404:
		weight[x][y][WT]++;
		weight[x - 1][y + 1][WT]++;
		weight[x - 2][y + 2][WT]++;
		break;
		//4
	case 105:
		weight[x + 1][y][WT] += linear_weight;
		weight[x + 4][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 205:
		weight[x][y + 1][WT] += linear_weight;
		weight[x][y + 4][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 305:
		weight[x + 1][y + 1][WT] += linear_weight;
		weight[x + 4][y + 4][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 405:
		weight[x - 1][y + 1][WT] += linear_weight;
		weight[x - 4][y + 4][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//5
	case 106:
		weight[x][y][WT]++;
		weight[x + 2][y][WT] += linear_weight;
		weight[x + 5][y][WT]++;
		break;
	case 206:
		weight[x][y][WT]++;
		weight[x][y + 2][WT] += linear_weight;
		weight[x][y + 5][WT]++;
		break;
	case 306:
		weight[x][y][WT]++;
		weight[x + 2][y + 2][WT] += linear_weight;
		weight[x + 5][y + 5][WT]++;
		break;
	case 406:
		weight[x][y][WT]++;
		weight[x - 2][y + 2][WT] += linear_weight;
		weight[x - 5][y + 5][WT]++;
		break;
		//6
	case 107:
		weight[x][y][WT]++;
		weight[x + 1][y][WT]++;
		weight[x + 3][y][WT]++;
		break;
	case 207:
		weight[x][y][WT]++;
		weight[x][y + 1][WT]++;
		weight[x][y + 3][WT]++;
		break;
	case 307:
		weight[x][y][WT]++;
		weight[x + 1][y + 1][WT]++;
		weight[x + 3][y + 3][WT]++;
		break;
	case 407:
		weight[x][y][WT]++;
		weight[x - 1][y + 1][WT]++;
		weight[x - 3][y + 3][WT]++;
		break;
		//7
	case 108:
		weight[x + 2][y][WT]++;
		weight[x + 4][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 208:
		weight[x][y + 2][WT]++;
		weight[x][y + 4][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 308:
		weight[x + 2][y + 2][WT]++;
		weight[x + 4][y + 4][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 408:
		weight[x - 2][y + 2][WT]++;
		weight[x - 4][y + 4][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//8
	case 109:
		weight[x][y][WT]++;
		weight[x + 3][y][WT] += linear_weight;
		weight[x + 5][y][WT]++;
		break;
	case 209:
		weight[x][y][WT]++;
		weight[x][y + 3][WT] += linear_weight;
		weight[x][y + 5][WT]++;
		break;
	case 309:
		weight[x][y][WT]++;
		weight[x + 3][y + 3][WT] += linear_weight;
		weight[x + 5][y + 5][WT]++;
		break;
	case 409:
		weight[x][y][WT]++;
		weight[x - 3][y + 3][WT] += linear_weight;
		weight[x - 5][y + 5][WT]++;
		break;
		//9
	case 110:
		weight[x][y][WT]++;
		weight[x + 1][y][WT]++;
		weight[x + 4][y][WT]++;
		break;
	case 210:
		weight[x][y][WT]++;
		weight[x][y + 1][WT]++;
		weight[x][y + 4][WT]++;
		break;
	case 310:
		weight[x][y][WT]++;
		weight[x + 1][y + 1][WT]++;
		weight[x + 4][y + 4][WT]++;
		break;
	case 410:
		weight[x][y][WT]++;
		weight[x - 1][y + 1][WT]++;
		weight[x - 4][y + 4][WT]++;
		break;
		//10
	case 111:
		weight[x + 1][y][WT]++;
		weight[x + 3][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 211:
		weight[x][y + 1][WT]++;
		weight[x][y + 3][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 311:
		weight[x + 1][y + 1][WT]++;
		weight[x + 3][y + 3][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 411:
		weight[x - 1][y + 1][WT]++;
		weight[x - 3][y + 3][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//11
	case 112:
		weight[x][y][WT]++;
		weight[x + 4][y][WT]++;
		weight[x + 2][y][WT]++;
		break;
	case 212:
		weight[x][y][WT]++;
		weight[x][y + 4][WT]++;
		weight[x][y + 2][WT]++;
		break;
	case 312:
		weight[x][y][WT]++;
		weight[x + 4][y + 4][WT]++;
		weight[x + 2][y + 2][WT]++;
		break;
	case 412:
		weight[x][y][WT]++;
		weight[x - 4][y + 4][WT]++;
		weight[x - 2][y + 2][WT]++;
		break;
		//12
	case 113:
		weight[x + 1][y][WT]++;
		weight[x + 2][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 213:
		weight[x][y + 1][WT]++;
		weight[x][y + 2][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 313:
		weight[x + 1][y + 1][WT]++;
		weight[x + 2][y + 2][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 413:
		weight[x - 1][y + 1][WT]++;
		weight[x - 2][y + 2][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//13
	case 114:
		weight[x][y][WT]++;
		weight[x + 3][y][WT]++;
		weight[x + 2][y][WT]++;
		break;
	case 214:
		weight[x][y][WT]++;
		weight[x][y + 3][WT]++;
		weight[x][y + 2][WT]++;
		break;
	case 314:
		weight[x][y][WT]++;
		weight[x + 3][y + 3][WT]++;
		weight[x + 2][y + 2][WT]++;
		break;
	case 414:
		weight[x][y][WT]++;
		weight[x - 3][y + 3][WT]++;
		weight[x - 2][y + 2][WT]++;
		break;
		//14
	case 115:
		weight[x + 3][y][WT]++;
		weight[x + 1][y][WT]++;
		weight[x + 2][y][WT]++;
		break;
	case 215:
		weight[x][y + 3][WT]++;
		weight[x][y + 1][WT]++;
		weight[x][y + 2][WT]++;
		break;
	case 315:
		weight[x + 3][y + 3][WT]++;
		weight[x + 1][y + 1][WT]++;
		weight[x + 2][y + 2][WT]++;
		break;
	case 415:
		weight[x - 3][y + 3][WT]++;
		weight[x - 1][y + 1][WT]++;
		weight[x - 2][y + 2][WT]++;
		break;
		//15
	case 116:
		weight[x + 3][y][WT]++;
		weight[x + 2][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 216:
		weight[x][y + 3][WT]++;
		weight[x][y + 2][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 316:
		weight[x + 3][y + 3][WT]++;
		weight[x + 2][y + 2][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 416:
		weight[x - 3][y + 3][WT]++;
		weight[x - 2][y + 2][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//16
	case 117:
		weight[x + 3][y][WT]++;
		weight[x + 4][y][WT]++;
		weight[x][y][WT]++;
		break;
	case 217:
		weight[x][y + 3][WT]++;
		weight[x][y + 4][WT]++;
		weight[x][y][WT]++;
		break;
	case 317:
		weight[x + 3][y + 3][WT]++;
		weight[x + 4][y + 4][WT]++;
		weight[x][y][WT]++;
		break;
	case 417:
		weight[x - 3][y + 3][WT]++;
		weight[x - 4][y + 4][WT]++;
		weight[x][y][WT]++;
		break;
		//17
	case 118:
		weight[x + 3][y][WT]++;
		weight[x + 4][y][WT]++;
		weight[x + 2][y][WT]++;
		break;
	case 218:
		weight[x][y + 3][WT]++;
		weight[x][y + 4][WT]++;
		weight[x][y + 2][WT]++;
		break;
	case 318:
		weight[x + 3][y + 3][WT]++;
		weight[x + 4][y + 4][WT]++;
		weight[x + 2][y + 2][WT]++;
		break;
	case 418:
		weight[x - 3][y + 3][WT]++;
		weight[x - 4][y + 4][WT]++;
		weight[x - 2][y + 2][WT]++;
		break;
		//18
	case 119:
		weight[x + 3][y][WT]++;
		weight[x + 4][y][WT]++;
		weight[x + 1][y][WT]++;
		break;
	case 219:
		weight[x][y + 3][WT]++;
		weight[x][y + 4][WT]++;
		weight[x][y + 1][WT]++;
		break;
	case 319:
		weight[x + 3][y + 3][WT]++;
		weight[x + 4][y + 4][WT]++;
		weight[x + 1][y + 1][WT]++;
		break;
	case 419:
		weight[x - 3][y + 3][WT]++;
		weight[x - 4][y + 4][WT]++;
		weight[x - 1][y + 1][WT]++;
		break;
		//19
	case 120:
		weight[x + 1][y][WT]++;
		weight[x + 2][y][WT]++;
		weight[x + 4][y][WT]++;
		break;
	case 220:
		weight[x][y + 1][WT]++;
		weight[x][y + 2][WT]++;
		weight[x][y + 4][WT]++;
		break;
	case 320:
		weight[x + 1][y + 1][WT]++;
		weight[x + 2][y + 2][WT]++;
		weight[x + 4][y + 4][WT]++;
		break;
	case 420:
		weight[x - 1][y + 1][WT]++;
		weight[x - 2][y + 2][WT]++;
		weight[x - 4][y + 4][WT]++;
		break;
		//20
	case 121:
		weight[x + 2][y][WT]++;
		weight[x + 3][y][WT]++;
		weight[x + 4][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 221:
		weight[x][y + 2][WT]++;
		weight[x][y + 3][WT]++;
		weight[x][y + 4][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 321:
		weight[x + 2][y + 2][WT]++;
		weight[x + 3][y + 3][WT]++;
		weight[x + 4][y + 4][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 421:
		weight[x - 2][y + 2][WT]++;
		weight[x - 3][y + 3][WT]++;
		weight[x - 4][y + 4][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//21
	case 122:
		weight[x][y][WT]++;
		weight[x + 3][y][WT]++;
		weight[x + 4][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 222:
		weight[x][y][WT]++;
		weight[x][y + 3][WT]++;
		weight[x][y + 4][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 322:
		weight[x][y][WT]++;
		weight[x + 3][y + 3][WT]++;
		weight[x + 4][y + 4][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 422:
		weight[x][y][WT]++;
		weight[x - 3][y + 3][WT]++;
		weight[x - 4][y + 4][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//22
	case 123:
		weight[x][y][WT]++;
		weight[x + 1][y][WT]++;
		weight[x + 4][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 223:
		weight[x][y][WT]++;
		weight[x][y + 1][WT]++;
		weight[x][y + 4][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 323:
		weight[x][y][WT]++;
		weight[x + 1][y + 1][WT]++;
		weight[x + 4][y + 4][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 423:
		weight[x][y][WT]++;
		weight[x - 1][y + 1][WT]++;
		weight[x - 4][y + 4][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//23
	case 124:
		weight[x][y][WT]++;
		weight[x + 1][y][WT]++;
		weight[x + 2][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 224:
		weight[x][y][WT]++;
		weight[x][y + 1][WT]++;
		weight[x][y + 2][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 324:
		weight[x][y][WT]++;
		weight[x + 1][y + 1][WT]++;
		weight[x + 2][y + 2][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 424:
		weight[x][y][WT]++;
		weight[x - 1][y + 1][WT]++;
		weight[x - 2][y + 2][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//24
	case 125:
		weight[x][y][WT]++;
		weight[x + 1][y][WT]++;
		weight[x + 2][y][WT]++;
		weight[x + 3][y][WT]++;
		break;
	case 225:
		weight[x][y][WT]++;
		weight[x][y + 1][WT]++;
		weight[x][y + 2][WT]++;
		weight[x][y + 3][WT]++;
		break;
	case 325:
		weight[x][y][WT]++;
		weight[x + 1][y + 1][WT]++;
		weight[x + 2][y + 2][WT]++;
		weight[x + 3][y + 3][WT]++;
		break;
	case 425:
		weight[x][y][WT]++;
		weight[x - 1][y + 1][WT]++;
		weight[x - 2][y + 2][WT]++;
		weight[x - 3][y + 3][WT]++;
		break;
		//25
	case 126:
		weight[x + 1][y][WT]++;
		weight[x + 3][y][WT]++;
		weight[x + 4][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 226:
		weight[x][y + 1][WT]++;
		weight[x][y + 3][WT]++;
		weight[x][y + 4][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 326:
		weight[x + 1][y + 1][WT]++;
		weight[x + 3][y + 3][WT]++;
		weight[x + 4][y + 4][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 426:
		weight[x - 1][y + 1][WT]++;
		weight[x - 3][y + 3][WT]++;
		weight[x - 4][y + 4][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//26
	case 127:
		weight[x][y][WT]++;
		weight[x + 2][y][WT]++;
		weight[x + 4][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 227:
		weight[x][y][WT]++;
		weight[x][y + 2][WT]++;
		weight[x][y + 4][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 327:
		weight[x][y][WT]++;
		weight[x + 2][y + 2][WT]++;
		weight[x + 4][y + 4][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 427:
		weight[x][y][WT]++;
		weight[x - 2][y + 2][WT]++;
		weight[x - 4][y + 4][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//27
	case 128:
		weight[x][y][WT]++;
		weight[x + 1][y][WT]++;
		weight[x + 3][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 228:
		weight[x][y][WT]++;
		weight[x][y + 1][WT]++;
		weight[x][y + 3][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 328:
		weight[x][y][WT]++;
		weight[x + 1][y + 1][WT]++;
		weight[x + 3][y + 3][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 428:
		weight[x][y][WT]++;
		weight[x - 1][y + 1][WT]++;
		weight[x - 3][y + 3][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//28
	case 129:
		weight[x][y][WT]++;
		weight[x + 1][y][WT]++;
		weight[x + 2][y][WT]++;
		weight[x + 4][y][WT]++;
		break;
	case 229:
		weight[x][y][WT]++;
		weight[x][y + 1][WT]++;
		weight[x][y + 2][WT]++;
		weight[x][y + 4][WT]++;
		break;
	case 329:
		weight[x][y][WT]++;
		weight[x + 1][y + 1][WT]++;
		weight[x + 2][y + 2][WT]++;
		weight[x + 4][y + 4][WT]++;
		break;
	case 429:
		weight[x][y][WT]++;
		weight[x - 1][y + 1][WT]++;
		weight[x - 2][y + 2][WT]++;
		weight[x - 4][y + 4][WT]++;
		break;
		//29
	case 130:
		weight[x + 1][y][WT]++;
		weight[x + 2][y][WT]++;
		weight[x + 4][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 230:
		weight[x][y + 1][WT]++;
		weight[x][y + 2][WT]++;
		weight[x][y + 4][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 330:
		weight[x + 1][y + 1][WT]++;
		weight[x + 2][y + 2][WT]++;
		weight[x + 4][y + 4][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 430:
		weight[x - 1][y + 1][WT]++;
		weight[x - 2][y + 2][WT]++;
		weight[x - 4][y + 4][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//30
	case 131:
		weight[x][y][WT]++;
		weight[x + 2][y][WT]++;
		weight[x + 3][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 231:
		weight[x][y][WT]++;
		weight[x][y + 2][WT]++;
		weight[x][y + 3][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 331:
		weight[x][y][WT]++;
		weight[x + 2][y + 2][WT]++;
		weight[x + 3][y + 3][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 431:
		weight[x][y][WT]++;
		weight[x - 2][y + 2][WT]++;
		weight[x - 3][y + 3][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//31
	case 132:
		weight[x][y][WT]++;
		weight[x + 1][y][WT]++;
		weight[x + 3][y][WT]++;
		weight[x + 4][y][WT]++;
		break;
	case 232:
		weight[x][y][WT]++;
		weight[x][y + 1][WT]++;
		weight[x][y + 3][WT]++;
		weight[x][y + 4][WT]++;
		break;
	case 332:
		weight[x][y][WT]++;
		weight[x + 1][y + 1][WT]++;
		weight[x + 3][y + 3][WT]++;
		weight[x + 4][y + 4][WT]++;
		break;
	case 432:
		weight[x][y][WT]++;
		weight[x - 1][y + 1][WT]++;
		weight[x - 3][y + 3][WT]++;
		weight[x - 4][y + 4][WT]++;
		break;
		//32
	case 133:
		weight[x + 1][y][WT]++;
		weight[x + 2][y][WT]++;
		weight[x + 3][y][WT]++;
		weight[x + 5][y][WT]++;
		break;
	case 233:
		weight[x][y + 1][WT]++;
		weight[x][y + 2][WT]++;
		weight[x][y + 3][WT]++;
		weight[x][y + 5][WT]++;
		break;
	case 333:
		weight[x + 1][y + 1][WT]++;
		weight[x + 2][y + 2][WT]++;
		weight[x + 3][y + 3][WT]++;
		weight[x + 5][y + 5][WT]++;
		break;
	case 433:
		weight[x - 1][y + 1][WT]++;
		weight[x - 2][y + 2][WT]++;
		weight[x - 3][y + 3][WT]++;
		weight[x - 5][y + 5][WT]++;
		break;
		//33
	case 134:
		weight[x][y][WT]++;
		weight[x + 2][y][WT]++;
		weight[x + 3][y][WT]++;
		weight[x + 4][y][WT]++;
		break;
	case 234:
		weight[x][y][WT]++;
		weight[x][y + 2][WT]++;
		weight[x][y + 3][WT]++;
		weight[x][y + 4][WT]++;
		break;
	case 334:
		weight[x][y][WT]++;
		weight[x + 2][y + 2][WT]++;
		weight[x + 3][y + 3][WT]++;
		weight[x + 4][y + 4][WT]++;
		break;
	case 434:
		weight[x][y][WT]++;
		weight[x - 2][y + 2][WT]++;
		weight[x - 3][y + 3][WT]++;
		weight[x - 4][y + 4][WT]++;
		break;
		//34
	case 135:
		weight[x + 1][y][WT]++;
		weight[x + 2][y][WT]++;
		weight[x + 3][y][WT]++;
		weight[x + 4][y][WT]++;
		break;
	case 235:
		weight[x][y + 1][WT]++;
		weight[x][y + 2][WT]++;
		weight[x][y + 3][WT]++;
		weight[x][y + 4][WT]++;
		break;
	case 335:
		weight[x + 1][y + 1][WT]++;
		weight[x + 2][y + 2][WT]++;
		weight[x + 3][y + 3][WT]++;
		weight[x + 4][y + 4][WT]++;
		break;
	case 435:
		weight[x - 1][y + 1][WT]++;
		weight[x - 2][y + 2][WT]++;
		weight[x - 3][y + 3][WT]++;
		weight[x - 4][y + 4][WT]++;
		break;
		//35
	}

}

void clear_weight(int weight[19][19][9])
{//weight를 초기화 하는 함수
	for (int i = 0; i < 19; i++)
	{
		for (int j = 0; j < 19; j++)
		{
			for (int k = 0; k < 9; k++)
				weight[i][j][k] = 0;
		}
	}
}

void myturn(int cnt) {
	if (terminateAI) return;
	int x[2], y[2];

	// 이 부분에서 알고리즘 프로그램(AI)을 작성하십시오. 기본 제공된 코드를 수정 또는 삭제하고 본인이 코드를 사용하시면 됩니다.
	// 현재 Sample code의 AI는 Random으로 돌을 놓는 Algorithm이 작성되어 있습니다.
	int i, j, k, l;
	int count = 0;
	int Wincase;
	int search[6];
	int s3_1[7];
	int s3_2[8];



	////////////////////////// 첫 수 /////////////////////////////
	srand((unsigned)time(NULL));
	
	if (cnt == 1)
	{
		do {
			x[0] = (rand() % 3) + 8;
			y[0] = (rand() % 3) + 8;
		} while (!isFree(x[0], y[0]));

		domymove(x, y, cnt);
		return;
	}



	////////////////////////// 필승 검사 /////////////////////////
	
	//가로 검사
	for (i = 0; i < 14; i++)
	{
		for (j = 0; j < 19; j++)
		{
			for (k = 0; k < 6; k++)
			{
				search[k] = myBoard(x[0], y[0], count, i+k, j);
				if (search[k] == 3)
					search[k] = 1;
			}

			Wincase = AWin_case(search);
			if (Wincase != 0)
			{
				if (i > 0 && myBoard(x[0], y[0], count, i - 1, j) == 1)
					continue;
				
				if (i + 6 < 19 && myBoard(x[0], y[0], count, i + 6, j) == 1)
					continue;

				switch (Wincase)
				{
					case 1:
						x[0] = i + 4;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 5;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 2:
						x[0] = i;		y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 5;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 3:
						x[0] = i;		y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 1;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 4:
						x[0] = i + 1;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 5;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 5:
						x[0] = i;		y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 2;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 6:
						x[0] = i + 1;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 2;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 7:
						x[0] = i + 2;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 5;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 8:
						x[0] = i;		y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 3;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 9:
						x[0] = i + 2;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 3;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 10:
						x[0] = i + 3;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 5;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 11:
						x[0] = i;		y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 4;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 12:
						x[0] = i + 3;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 4;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 13:
						x[0] = i + 5;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						break;
					case 14:
						x[0] = i;		y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						break;
					case 15:
						x[0] = i + 1;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						break;
					case 16:
						x[0] = i + 2;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						break;
					case 17:
						x[0] = i + 3;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						break;
					case 18:
						x[0] = i + 4;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						break;
					case 19:
						x[0] = i + 2;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 4;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 20:
						x[0] = i + 1;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 4;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
					case 21:
						x[0] = i + 1;	y[0] = j;
						if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
						else break;
						x[1] = i + 3;	y[1] = j;
						if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
						else { count = 0;  break; }
						break;
				}

				if (count == 2)
				{
					domymove(x, y, cnt);
					return;
				}
				else if(count == 1)
				{
					do {
						x[1] = rand() % width;
						y[1] = rand() % height;
					} while (!isFree(x[1], y[1]) || !is_OK(x[0], y[0], count, x[1], y[1]));

					domymove(x, y, cnt);
					return;
				}
			}
		}
	}

	//세로 검사
	for (i = 0; i < 19; i++)
	{
		for (j = 0; j < 14; j++)
		{
			for (k = 0; k < 6; k++)
			{
				search[k] = myBoard(x[0], y[0], count, i, j + k);
				if (search[k] == 3)
					search[k] = 1;
			}

			Wincase = AWin_case(search);
			if (Wincase != 0)
			{
				if (j > 0 && myBoard(x[0], y[0], count, i, j - 1) == 1)
					continue;

				if (j + 6 < 19 && myBoard(x[0], y[0], count, i, j + 6) == 1)
					continue;

				switch (Wincase)
				{
				case 1:
					x[0] = i;		y[0] = j + 4;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 5;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 2:
					x[0] = i;		y[0] = j; 
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 5; 
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 3:
					x[0] = i;		y[0] = j; 
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 1;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 4:
					x[0] = i;		y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 5;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 5:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 2;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 6:
					x[0] = i;		y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 2;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 7:
					x[0] = i;		y[0] = j + 2;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 5;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 8:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 3;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 9:
					x[0] = i;		y[0] = j + 2;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 3;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 10:
					x[0] = i;		y[0] = j + 3;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 5;
					break;
				case 11:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 4;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 12:
					x[0] = i;		y[0] = j + 3;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 4;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 13:
					x[0] = i;		y[0] = j + 5;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 14:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 15:
					x[0] = i;		y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 16:
					x[0] = i;		y[0] = j + 2;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 17:
					x[0] = i;		y[0] = j + 3;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 18:
					x[0] = i;		y[0] = j + 4;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 19:
					x[0] = i;		y[0] = j + 2;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 4;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 20:
					x[0] = i;		y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 4;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 21:
					x[0] = i;		y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i;		y[1] = j + 3;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				}

				if (count == 2)
				{
					domymove(x, y, cnt);
					return;
				}
				else if (count == 1)
				{
					do {
						x[1] = rand() % width;
						y[1] = rand() % height;
					} while (!isFree(x[1], y[1]) || !is_OK(x[0], y[0], count, x[1], y[1]));

					domymove(x, y, cnt);
					return;
				}
			}
		}
	}

	//오른쪽 대각선 검사
	for (i = 0; i < 14; i++)
	{
		for (j = 0; j < 14; j++)
		{
			for (k = 0; k < 6; k++)
			{
				search[k] = myBoard(x[0], y[0], count, i + k, j + k);
				if (search[k] == 3)
					search[k] = 1;
			}

			Wincase = AWin_case(search);
			if (Wincase != 0)
			{
				if (i > 0 && j > 0 && myBoard(x[0], y[0], count, i - 1, j - 1) == 1)
					continue;

				if (i + 6 < 19 && j + 6 < 19 && myBoard(x[0], y[0], count, i + 6, j + 6) == 1)
					continue;

				switch (Wincase)
				{
				case 1:
					x[0] = i + 4;	y[0] = j + 4;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 5;	y[1] = j + 5;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 2:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 5;	y[1] = j + 5;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 3:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 1;	y[1] = j + 1;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 4:
					x[0] = i + 1;	y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 5;	y[1] = j + 5;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 5:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 2;	y[1] = j + 2;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 6:
					x[0] = i + 1;	y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 2;	y[1] = j + 2;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 7:
					x[0] = i + 2;	y[0] = j + 2;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 5;	y[1] = j + 5;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 8:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 3;	y[1] = j + 3;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 9:
					x[0] = i + 2;	y[0] = j + 2;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 3;	y[1] = j + 3;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 10:
					x[0] = i + 3;	y[0] = j + 3;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 5;	y[1] = j + 5;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 11:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 4;	y[1] = j + 4;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 12:
					x[0] = i + 3;	y[0] = j + 3;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 4;	y[1] = j + 4;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 13:
					x[0] = i + 5;	y[0] = j + 5;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 14:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 15:
					x[0] = i + 1;	y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 16:
					x[0] = i + 2;	y[0] = j + 2;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 17:
					x[0] = i + 3;	y[0] = j + 3;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 18:
					x[0] = i + 4;	y[0] = j + 4;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 19:
					x[0] = i + 2;	y[0] = j + 2;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 4;	y[1] = j + 4;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 20:
					x[0] = i + 1;	y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 4;	y[1] = j + 4;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 21:
					x[0] = i + 1;	y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i + 3;	y[1] = j + 3;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				}

				if (count == 2)
				{
					domymove(x, y, cnt);
					return;
				}
				else if (count == 1)
				{
					do {
						x[1] = rand() % width;
						y[1] = rand() % height;
					} while (!isFree(x[1], y[1]) || !is_OK(x[0], y[0], count, x[1], y[1]));

					domymove(x, y, cnt);
					return;
				}
			}
		}
	}

	//왼쪽 대각선 검사
	for (i = 5; i < 19; i++)
	{
		for (j = 0; j < 14; j++)
		{
			for (k = 0; k < 6; k++)
			{
				search[k] = myBoard(x[0], y[0], count, i - k, j + k);
				if (search[k] == 3)
					search[k] = 1;
			}

			Wincase = AWin_case(search);
			if (Wincase != 0)
			{
				if (i + 1 < 19 && j > 0 && myBoard(x[0], y[0], count, i + 1, j - 1) == 1)
					continue;

				if (i - 6 >= 0 && j + 6 < 19 && myBoard(x[0], y[0], count, i - 6, j + 6) == 1)
					continue;

				switch (Wincase)
				{
				case 1:
					x[0] = i - 4;	y[0] = j + 4;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 5;	y[1] = j + 5;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 2:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 5;	y[1] = j + 5;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 3:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 1;	y[1] = j + 1;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 4:
					x[0] = i - 1;	y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 5;	y[1] = j + 5;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 5:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 2;	y[1] = j + 2;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 6:
					x[0] = i - 1;	y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 2;	y[1] = j + 2;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 7:
					x[0] = i - 2;	y[0] = j + 2;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 5;	y[1] = j + 5;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 8:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 3;	y[1] = j + 3;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 9:
					x[0] = i - 2;	y[0] = j + 2;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 3;	y[1] = j + 3;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 10:
					x[0] = i - 3;	y[0] = j + 3;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 5;	y[1] = j + 5;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 11:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 4;	y[1] = j + 4;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 12:
					x[0] = i - 3;	y[0] = j + 3;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 4;	y[1] = j + 4;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 13:
					x[0] = i - 5;	y[0] = j + 5;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 14:
					x[0] = i;		y[0] = j;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 15:
					x[0] = i - 1;	y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 16:
					x[0] = i - 2;	y[0] = j + 2;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 17:
					x[0] = i - 3;	y[0] = j + 3;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 18:
					x[0] = i - 4;	y[0] = j + 4;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					break;
				case 19:
					x[0] = i - 2;	y[0] = j + 2;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 4;	y[1] = j + 4;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 20:
					x[0] = i - 1;	y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 4;	y[1] = j + 4;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				case 21:
					x[0] = i - 1;	y[0] = j + 1;
					if (is_OK(x[0], y[0], count, x[0], y[0])) count++;
					else break;

					x[1] = i - 3;	y[1] = j + 3;
					if (is_OK(x[0], y[0], count, x[1], y[1])) count++;
					else { count = 0;  break; }
					break;
				}

				if (count == 2)
				{
					domymove(x, y, cnt);
					return;
				}
				else if (count == 1)
				{
					do {
						x[1] = rand() % width;
						y[1] = rand() % height;
					} while (!isFree(x[1], y[1]) || !is_OK(x[0], y[0], count, x[1], y[1]));

					domymove(x, y, cnt);
					return;
				}
			}
		}
	}



	////////////////////////// 막 기 ////////////////////////////

	int Protect1[3][6] = {  {0, 2, 2, 2, 2, 0},			// 1
							{2, 2, 2, 2, 2, 0},			// 2
							{0, 2, 2, 2, 2, 2}			// 3
	};

	int Protect2[19][6] = { {2, 2, 2, 2, 0, 0},			// 4
							{0, 0, 2, 2, 2, 2},			// 5
							{1, 2, 2, 2, 2, 0},			// 6
							{0, 2, 2, 2, 2, 1},			// 7
							{2, 2, 0, 2, 2, 2},			// 8
							{2, 2, 2, 0, 2, 2},			// 9
							{2, 0, 0, 2, 2, 2},			// 10
							{2, 2, 2, 0, 0, 2},			// 11
							{2, 2, 0, 2, 0, 2},			// 12
							{2, 0, 2, 0, 2, 2},			// 13
							{2, 0, 2, 2, 0, 2},			// 14
							{0, 2, 2, 2, 0, 2},			// 15
							{0, 2, 0, 2, 2, 2},			// 16
							{2, 2, 2, 0, 2, 0},			// 17
							{2, 0, 2, 2, 2, 0},			// 18
							{2, 2, 2, 2, 0, 2},			// 19
							{2, 0, 2, 2, 2, 2},			// 20
							{2, 2, 0, 2, 2, 0},			// 21
							{0, 2, 2, 0, 2, 2}			// 22

	};

	int Protect2_location[19] = { 4, 1, 5, 0, 2, 3, 2, 3, 2, 3, 1, 4, 2, 3, 1, 4, 1, 2, 3 };
	int p_case = 19;

	//case 1
	//가로
	for (i = 0; i < 14; i++)
	{
		for (j = 0; j < 19; j++)
		{
			for (k = 0; k < 6; k++)
			{
				search[k] = myBoard(x[0], y[0], count, i + k, j);
				if (search[k] == 3)
					search[k] = 2;
			}

			if (Arr_Equal(search, Protect1[0]))
			{
				x[count] = i;		y[count] = j;
				if (is_OK(x[0], y[0], count, x[count], y[count]) && !(i > 0 && myBoard(x[0], y[0], count, i - 1, j) == 1)) count++;
				else continue;

				if (count == 2)
				{
					domymove(x, y, cnt);
					return;
				}

				x[count] = i + 5;	y[count] = j;
				if (is_OK(x[0], y[0], count, x[count], y[count]) && !(i < 13 && myBoard(x[0], y[0], count, i + 6, j) == 1)) count++;
				else continue;

				if (count == 2)
				{
					domymove(x, y, cnt);
					return;
				}
			}
		}
	}

	//세로
	for (i = 0; i < 19; i++)
	{
		for (j = 0; j < 14; j++)
		{
			for (k = 0; k < 6; k++)
			{
				search[k] = myBoard(x[0], y[0], count, i, j + k);
				if (search[k] == 3)
					search[k] = 2;
			}

			if (Arr_Equal(search, Protect1[0]))
			{
				x[count] = i;		y[count] = j;
				if (is_OK(x[0], y[0], count, x[count], y[count]) && !(j > 0 && myBoard(x[0], y[0], count, i, j - 1) == 1)) count++;
				else continue;

				if (count == 2)
				{
					domymove(x, y, cnt);
					return;
				}

				x[count] = i;		y[count] = j + 5;
				if (is_OK(x[0], y[0], count, x[count], y[count]) && !(j < 13 && myBoard(x[0], y[0], count, i, j + 6) == 1)) count++;
				else continue;

				if (count == 2)
				{
					domymove(x, y, cnt);
					return;
				}
			}
		}
	}

	//오른쪽 대각선
	for (i = 0; i < 14; i++)
	{
		for (j = 0; j < 14; j++)
		{
			for (k = 0; k < 6; k++)
			{
				search[k] = myBoard(x[0], y[0], count, i + k, j + k);
				if (search[k] == 3)
					search[k] = 2;
			}

			if (Arr_Equal(search, Protect1[0]))
			{
				x[count] = i;		y[count] = j;
				if (is_OK(x[0], y[0], count, x[count], y[count]) && !(i > 0 && j > 0 && myBoard(x[0], y[0], count, i - 1, j - 1) == 1)) count++;
				else continue;

				if (count == 2)
				{
					domymove(x, y, cnt);
					return;
				}

				x[count] = i + 5;	y[count] = j + 5;
				if (is_OK(x[0], y[0], count, x[count], y[count]) && !(i < 13 && j < 13 && myBoard(x[0], y[0], count, i + 6, j + 6) == 1)) count++;
				else continue;

				if (count == 2)
				{
					domymove(x, y, cnt);
					return;
				}
			}
		}
	}

	//왼쪽 대각선
	for (i = 5; i < 19; i++)
	{
		for (j = 0; j < 14; j++)
		{
			for (k = 0; k < 6; k++)
			{
				search[k] = myBoard(x[0], y[0], count, i - k, j + k);
				if (search[k] == 3)
					search[k] = 2;
			}

			if (Arr_Equal(search, Protect1[0]))
			{
				x[count] = i;		y[count] = j;
				if (is_OK(x[0], y[0], count, x[count], y[count]) && !(i + 1 < 19 && j > 0 && myBoard(x[0], y[0], count, i + 1, j - 1) == 1)) count++;
				else continue;

				if (count == 2)
				{
					domymove(x, y, cnt);
					return;
				}

				x[count] = i - 5;	y[count] = j + 5;
				if (is_OK(x[0], y[0], count, x[count], y[count]) && !(i > 5 && j < 13 && myBoard(x[0], y[0], count, i - 6, j + 6) == 1)) count++;
				else continue;

				if (count == 2)
				{
					domymove(x, y, cnt);
					return;
				}
			}
		}
	}


	//case 2, 3
	//가로
	for (i = 0; i < 14; i++)
	{
		for (j = 0; j < 19; j++)
		{
			for (k = 0; k < 6; k++)
			{
				search[k] = myBoard(x[0], y[0], count, i + k, j);
				if (search[k] == 3)
					search[k] = 2;
			}

			if (Arr_Equal(search, Protect1[1]))
			{
				if (i + 6 < 19 && myBoard(x[0], y[0], count, i + 6, j) == 2)
					continue;

				x[count] = i + 5;	y[count] = j;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}

				continue;
			}

			if (Arr_Equal(search, Protect1[2]))
			{
				if (i > 0 && myBoard(x[0], y[0], count, i - 1, j) == 2)
					continue;

				x[count] = i;		y[count] = j;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}

	//세로
	for (i = 0; i < 19; i++)
	{
		for (j = 0; j < 14; j++)
		{
			for (k = 0; k < 6; k++)
			{
				search[k] = myBoard(x[0], y[0], count, i, j + k);
				if (search[k] == 3)
					search[k] = 2;
			}

			if (Arr_Equal(search, Protect1[1]))
			{
				if (j + 6 < 19 && myBoard(x[0], y[0], count, i, j + 6) == 2)
					continue;

				x[count] = i;		y[count] = j + 5;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}

				continue;
			}

			if (Arr_Equal(search, Protect1[2]))
			{
				if (j > 0 && myBoard(x[0], y[0], count, i, j - 1) == 2)
					continue;

				x[count] = i;		y[count] = j;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}

	//오른쪽 대각선
	for (i = 0; i < 14; i++)
	{
		for (j = 0; j < 14; j++)
		{
			for (k = 0; k < 6; k++)
			{
				search[k] = myBoard(x[0], y[0], count, i + k, j + k);
				if (search[k] == 3)
					search[k] = 2;
			}

			if (Arr_Equal(search, Protect1[1]))
			{
				if (i + 6 < 19 && j + 6 < 19 && myBoard(x[0], y[0], count, i + 6, j + 6) == 2)
					continue;

				x[count] = i + 5;	y[count] = j + 5;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}

				continue;
			}

			if (Arr_Equal(search, Protect1[2]))
			{
				if (i > 0 && j > 0 && myBoard(x[0], y[0], count, i - 1, j - 1) == 2)
					continue;

				x[count] = i;		y[count] = j;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}

	//왼쪽 대각선
	for (i = 5; i < 19; i++)
	{
		for (j = 0; j < 14; j++)
		{
			for (k = 0; k < 6; k++)
			{
				search[k] = myBoard(x[0], y[0], count, i - k, j + k);
				if (search[k] == 3)
					search[k] = 2;
			}

			if (Arr_Equal(search, Protect1[1]))
			{
				if (i - 6 >= 0 && j + 6 < 19 && myBoard(x[0], y[0], count, i - 6, j + 6) == 2)
					continue;

				x[count] = i - 5;	y[count] = j + 5;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}

				continue;
			}

			if (Arr_Equal(search, Protect1[2]))
			{
				if (i + 1 < 19 && j > 0 && myBoard(x[0], y[0], count, i + 1, j - 1) == 2)
					continue;

				x[count] = i;		y[count] = j;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}


	//case 4~22
	for (l = 0; l < p_case; l++)
	{
		//가로
		for (i = 0; i < 14; i++)
		{
			for (j = 0; j < 19; j++)
			{
				for (k = 0; k < 6; k++)
				{
					search[k] = myBoard(x[0], y[0], count, i + k, j);
					if (search[k] == 3)
						search[k] = 2;
				}

				if (Arr_Equal(search, Protect2[l]))
				{
					if (l == 2)
						if ((i + 7 < 19 && myBoard(x[0], y[0], count, i + 7, j) == 2) || (i + 6 < 19 && myBoard(x[0], y[0], count, i + 6, j) == 1))
							continue;
					if (l == 3)
						if ((i - 1 > 0 && myBoard(x[0], y[0], count, i - 2, j) == 2) || (i > 0 && myBoard(x[0], y[0], count, i - 1, j) == 1))
							continue;
					if (l == 5 || l == 7 || l == 8 || l == 15)
						if (i + 6 < 19 && myBoard(x[0], y[0], count, i + 6, j) == 2)
							continue;
					if (l == 4 || l == 6 || l == 9 || l == 16)
						if (i > 0 && myBoard(x[0], y[0], count, i - 1, j) == 2)
							continue;
					if (l == 10)
						if ((i > 0 && myBoard(x[0], y[0], count, i - 1, j) == 2) || (i + 6 < 19 && myBoard(x[0], y[0], count, i + 6, j) == 2))
							continue;

					x[count] = i + Protect2_location[l];		y[count] = j;
					if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
					else continue;

					if (count == 2)
					{
						if (x[0] == x[1] && y[0] == y[1])
						{
							count--;
						}
						else
						{
							domymove(x, y, cnt);
							return;
						}
					}

					//continue;
				}
			}
		}

		//세로
		for (i = 0; i < 19; i++)
		{
			for (j = 0; j < 14; j++)
			{
				for (k = 0; k < 6; k++)
				{
					search[k] = myBoard(x[0], y[0], count, i, j + k);
					if (search[k] == 3)
						search[k] = 2;
				}

				if (Arr_Equal(search, Protect2[l]))
				{
					if (l == 2)
						if ((j + 7 < 19 && myBoard(x[0], y[0], count, i, j + 7) == 2) || (j + 6 < 19 && myBoard(x[0], y[0], count, i, j + 6) == 1))
							continue;
					if (l == 3)
						if ((j - 1 > 0 && myBoard(x[0], y[0], count, i, j - 2) == 2) || (j > 0 && myBoard(x[0], y[0], count, i, j - 1) == 1))
							continue;
					if (l == 5 || l == 7 || l == 8 || l == 15)
						if (j + 6 < 19 && myBoard(x[0], y[0], count, i, j + 6) == 2)
							continue;
					if (l == 4 || l == 6 || l == 9 || l == 16)
						if (j > 0 && myBoard(x[0], y[0], count, i, j - 1) == 2)
							continue;
					if (l == 10)
						if ((j > 0 && myBoard(x[0], y[0], count, i, j - 1) == 2) || (j + 6 < 19 && myBoard(x[0], y[0], count, i, j + 6) == 2))
							continue;

					x[count] = i;		y[count] = j + Protect2_location[l];
					if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
					else continue;

					if (count == 2)
					{
						if (x[0] == x[1] && y[0] == y[1])
						{
							count--;
						}
						else
						{
							domymove(x, y, cnt);
							return;
						}
					}

					//continue;
				}
			}
		}

		//오른쪽 대각선
		for (i = 0; i < 14; i++)
		{
			for (j = 0; j < 14; j++)
			{
				for (k = 0; k < 6; k++)
				{
					search[k] = myBoard(x[0], y[0], count, i + k, j + k);
					if (search[k] == 3)
						search[k] = 2;
				}

				if (Arr_Equal(search, Protect2[l]))
				{
					if (l == 2)
						if ((i + 7 < 19 && j + 7 < 19 && myBoard(x[0], y[0], count, i + 7, j + 7) == 2) || (i + 6 < 19 && j + 6 < 19 && myBoard(x[0], y[0], count, i + 6, j + 9) == 1))
							continue;
					if (l == 3)
						if ((i - 1 > 0 && j - 1 > 0 && myBoard(x[0], y[0], count, i - 2, j - 2) == 2) || (i > 0 && j > 0 && myBoard(x[0], y[0], count, i - 1, j - 1) == 1))
							continue;
					if (l == 5 || l == 7 || l == 8 || l == 15)
						if (i + 6 < 19 && j + 6 < 19 && myBoard(x[0], y[0], count, i + 6, j + 9) == 2)
							continue;
					if (l == 4 || l == 6 || l == 9 || l == 16)
						if (i > 0 && j > 0 && myBoard(x[0], y[0], count, i - 1, j - 1) == 2)
							continue;
					if (l == 10)
						if ((i > 0 && j > 0 && myBoard(x[0], y[0], count, i - 1, j - 1) == 2) || (i + 6 < 19 && j + 6 < 19 && myBoard(x[0], y[0], count, i + 6, j + 6) == 2))
							continue;

					x[count] = i + Protect2_location[l];		y[count] = j + Protect2_location[l];
					if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
					else continue;

					if (count == 2)
					{
						if (x[0] == x[1] && y[0] == y[1])
						{
							count--;
						}
						else
						{
							domymove(x, y, cnt);
							return;
						}
					}

					//continue;
				}
			}
		}

		//왼쪽 대각선
		for (i = 5; i < 19; i++)
		{
			for (j = 0; j < 14; j++)
			{
				for (k = 0; k < 6; k++)
				{
					search[k] = myBoard(x[0], y[0], count, i - k, j + k);
					if (search[k] == 3)
						search[k] = 2;
				}

				if (Arr_Equal(search, Protect2[l]))
				{
					if (l == 2)
						if ((i - 7 >= 0 && j + 7 < 19 && myBoard(x[0], y[0], count, i - 7, j + 7) == 2) || (i - 6 >= 0 && j + 6 < 19 && myBoard(x[0], y[0], count, i - 6, j + 9) == 1))
							continue;
					if (l == 3)
						if ((i + 2 < 19 && j - 1 > 0 && myBoard(x[0], y[0], count, i + 2, j - 2) == 2) || (i + 1 < 19 && j > 0 && myBoard(x[0], y[0], count, i + 1, j - 1) == 1))
							continue;
					if (l == 5 || l == 7 || l == 8 || l == 15)
						if (i - 6 >= 0 && j + 6 < 19 && myBoard(x[0], y[0], count, i - 6, j + 9) == 2)
							continue;
					if (l == 4 || l == 6 || l == 9 || l == 16)
						if (i + 1 < 19 && j > 0 && myBoard(x[0], y[0], count, i + 1, j - 1) == 2)
							continue;
					if (l == 10)
						if ((i + 1 < 19 && j > 0 && myBoard(x[0], y[0], count, i + 1, j - 1) == 2) || (i - 6 >= 0 && j + 6 < 19 && myBoard(x[0], y[0], count, i - 6, j + 6) == 2))
							continue;

					x[count] = i - Protect2_location[l];		y[count] = j + Protect2_location[l];
					if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
					else continue;

					if (count == 2)
					{
						if (x[0] == x[1] && y[0] == y[1])
						{
							count--;
						}
						else
						{
							domymove(x, y, cnt);
							return;
						}
					}

					//continue;
				}
			}
		}
	}


	//3개짜리 예방 
	//0022200
	//가로
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 19; j++)
		{
			for (k = 0; k < 7; k++)
			{
				s3_1[k] = myBoard(x[0], y[0], count, i + k, j);
				if (s3_1[k] == 3)
					s3_1[k] = 2;
			}
			
			if (s3_1[0] == 0 && s3_1[1] == 0 && s3_1[2] == 2 && s3_1[3] == 2 && s3_1[4] == 2 && s3_1[5] == 0 && s3_1[6] == 0)
			{
				if (Cross_4(i + 5, j) > Cross_4(i + 1, j))
				{
					x[count] = i + 5;		y[count] = j;
					if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
					else continue;
				}
				else if (Cross_4(i + 5, j) < Cross_4(i + 1, j))
				{
					x[count] = i + 1;		y[count] = j;
					if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
					else continue;
				}
				else
				{
					if (rand() % 2 == 0)
					{
						x[count] = i + 5;		y[count] = j;
						if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
						else continue;
					}
					else
					{
						x[count] = i + 1;		y[count] = j;
						if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
						else continue;
					}
				}

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}

	//세로
	for (i = 0; i < 19; i++)
	{
		for (j = 0; j < 13; j++)
		{
			for (k = 0; k < 7; k++)
			{
				s3_1[k] = myBoard(x[0], y[0], count, i, j + k);
				if (s3_1[k] == 3)
					s3_1[k] = 2;
			}

			if (s3_1[0] == 0 && s3_1[1] == 0 && s3_1[2] == 2 && s3_1[3] == 2 && s3_1[4] == 2 && s3_1[5] == 0 && s3_1[6] == 0)
			{
				if (Cross_4(i, j + 5) > Cross_4(i, j + 1))
				{
					x[count] = i;		y[count] = j + 5;
					if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
					else continue;
				}
				else if (Cross_4(i, j + 5) < Cross_4(i, j + 1))
				{
					x[count] = i;		y[count] = j + 1;
					if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
					else continue;
				}
				else
				{
					if (rand() % 2 == 0)
					{
						x[count] = i;		y[count] = j + 5;
						if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
						else continue;
					}
					else
					{
						x[count] = i;		y[count] = j + 1;
						if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
						else continue;
					}
				}

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}

	//오른쪽 대각선
	for (i = 0; i < 13; i++)
	{
		for (j = 0; j < 13; j++)
		{
			for (k = 0; k < 7; k++)
			{
				s3_1[k] = myBoard(x[0], y[0], count, i + k, j + k);
				if (s3_1[k] == 3)
					s3_1[k] = 2;
			}

			if (s3_1[0] == 0 && s3_1[1] == 0 && s3_1[2] == 2 && s3_1[3] == 2 && s3_1[4] == 2 && s3_1[5] == 0 && s3_1[6] == 0)
			{
				if (Cross_4(i + 5, j + 5) > Cross_4(i + 1, j + 1))
				{
					x[count] = i + 5;		y[count] = j + 5;
					if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
					else continue;
				}
				else if (Cross_4(i + 5, j + 5) < Cross_4(i + 1, j + 1))
				{
					x[count] = i + 1;		y[count] = j + 1;
					if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
					else continue;
				}
				else
				{
					if (rand() % 2 == 0)
					{
						x[count] = i + 5;		y[count] = j + 5;
						if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
						else continue;
					}
					else
					{
						x[count] = i + 1;		y[count] = j + 1;
						if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
						else continue;
					}
				}

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}

	//왼쪽 대각선
	for (i = 6; i < 19; i++)
	{
		for (j = 0; j < 13; j++)
		{
			for (k = 0; k < 7; k++)
			{
				s3_1[k] = myBoard(x[0], y[0], count, i - k, j + k);
				if (s3_1[k] == 3)
					s3_1[k] = 2;
			}

			if (s3_1[0] == 0 && s3_1[1] == 0 && s3_1[2] == 2 && s3_1[3] == 2 && s3_1[4] == 2 && s3_1[5] == 0 && s3_1[6] == 0)
			{
				if (Cross_4(i - 5, j + 5) > Cross_4(i - 1, j + 1))
				{
					x[count] = i - 5;		y[count] = j + 5;
					if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
					else continue;
				}
				else if (Cross_4(i - 5, j + 5) < Cross_4(i - 1, j + 1))
				{
					x[count] = i - 1;		y[count] = j + 1;
					if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
					else continue;
				}
				else
				{
					if (rand() % 2 == 0)
					{
						x[count] = i - 5;		y[count] = j + 5;
						if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
						else continue;
					}
					else
					{
						x[count] = i - 1;		y[count] = j + 1;
						if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
						else continue;
					}
				}

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}

		}
	}


	//00220200
	//가로
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 19; j++)
		{
			for (k = 0; k < 8; k++)
			{
				s3_2[k] = myBoard(x[0], y[0], count, i + k, j);
				if (s3_2[k] == 3)
					s3_2[k] = 2;
			}

			if (s3_2[0] == 0 && s3_2[1] == 0 && s3_2[2] == 2 && s3_2[3] == 2 && s3_2[4] == 0 && s3_2[5] == 2 && s3_2[6] == 0 && s3_2[7] == 0)
			{
				x[count] = i + 4;		y[count] = j;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;
				
				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}

	//세로
	for (i = 0; i < 19; i++)
	{
		for (j = 0; j < 12; j++)
		{
			for (k = 0; k < 8; k++)
			{
				s3_2[k] = myBoard(x[0], y[0], count, i, j + k);
				if (s3_2[k] == 3)
					s3_2[k] = 2;
			}

			if (s3_2[0] == 0 && s3_2[1] == 0 && s3_2[2] == 2 && s3_2[3] == 2 && s3_2[4] == 0 && s3_2[5] == 2 && s3_2[6] == 0 && s3_2[7] == 0)
			{
				x[count] = i;		y[count] = j + 4;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}

	//오른쪽 대각선
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			for (k = 0; k < 8; k++)
			{
				s3_2[k] = myBoard(x[0], y[0], count, i + k, j + k);
				if (s3_2[k] == 3)
					s3_2[k] = 2;
			}

			if (s3_2[0] == 0 && s3_2[1] == 0 && s3_2[2] == 2 && s3_2[3] == 2 && s3_2[4] == 0 && s3_2[5] == 2 && s3_2[6] == 0 && s3_2[7] == 0)
			{
				x[count] = i + 4;		y[count] = j + 4;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}

	//왼쪽 대각선
	for (i = 7; i < 19; i++)
	{
		for (j = 0; j < 12; j++)
		{
			for (k = 0; k < 8; k++)
			{
				s3_2[k] = myBoard(x[0], y[0], count, i - k, j + k);
				if (s3_2[k] == 3)
					s3_2[k] = 2;
			}

			if (s3_2[0] == 0 && s3_2[1] == 0 && s3_2[2] == 2 && s3_2[3] == 2 && s3_2[4] == 0 && s3_2[5] == 2 && s3_2[6] == 0 && s3_2[7] == 0)
			{
				x[count] = i - 4;		y[count] = j + 4;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}


	//00202200
	//가로
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 19; j++)
		{
			for (k = 0; k < 8; k++)
			{
				s3_2[k] = myBoard(x[0], y[0], count, i + k, j);
				if (s3_2[k] == 3)
					s3_2[k] = 2;
			}

			if (s3_2[0] == 0 && s3_2[1] == 0 && s3_2[2] == 2 && s3_2[3] == 0 && s3_2[4] == 2 && s3_2[5] == 2 && s3_2[6] == 0 && s3_2[7] == 0)
			{
				x[count] = i + 3;		y[count] = j;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}

	//세로
	for (i = 0; i < 19; i++)
	{
		for (j = 0; j < 12; j++)
		{
			for (k = 0; k < 8; k++)
			{
				s3_2[k] = myBoard(x[0], y[0], count, i, j + k);
				if (s3_2[k] == 3)
					s3_2[k] = 2;
			}

			if (s3_2[0] == 0 && s3_2[1] == 0 && s3_2[2] == 2 && s3_2[3] == 0 && s3_2[4] == 2 && s3_2[5] == 2 && s3_2[6] == 0 && s3_2[7] == 0)
			{
				x[count] = i;		y[count] = j + 3;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}

	//오른쪽 대각선
	for (i = 0; i < 12; i++)
	{
		for (j = 0; j < 12; j++)
		{
			for (k = 0; k < 8; k++)
			{
				s3_2[k] = myBoard(x[0], y[0], count, i + k, j + k);
				if (s3_2[k] == 3)
					s3_2[k] = 2;
			}

			if (s3_2[0] == 0 && s3_2[1] == 0 && s3_2[2] == 2 && s3_2[3] == 0 && s3_2[4] == 2 && s3_2[5] == 2 && s3_2[6] == 0 && s3_2[7] == 0)
			{
				x[count] = i + 3;		y[count] = j + 3;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}

	//왼쪽 대각선
	for (i = 7; i < 19; i++)
	{
		for (j = 0; j < 12; j++)
		{
			for (k = 0; k < 8; k++)
			{
				s3_2[k] = myBoard(x[0], y[0], count, i - k, j + k);
				if (s3_2[k] == 3)
					s3_2[k] = 2;
			}

			if (s3_2[0] == 0 && s3_2[1] == 0 && s3_2[2] == 2 && s3_2[3] == 0 && s3_2[4] == 2 && s3_2[5] == 2 && s3_2[6] == 0 && s3_2[7] == 0)
			{
				x[count] = i - 3;		y[count] = j + 3;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
		}
	}


	//십자 모양
	for (i = 0; i < 17; i++)
	{
		for (j = 0; j < 17; j++)
		{
			int b[3][3];
			
			for (k = 0; k < 3; k++)
			{
				for (l = 0; l < 3; l++)
				{
					b[k][l] = myBoard(x[0], y[0], count, i + k, j + l);
					if (b[k][l] == 3)
						b[k][l] = 2;
				}
			}

			if ((b[1][0] == 2 && b[0][1] == 2 && b[2][1] == 2 && b[1][2] == 2 && b[1][1] == 0) || (b[0][0] == 2 && b[2][0] == 2 && b[0][2] == 2 && b[2][2] == 2 && b[1][1] == 0))
			{
				x[count] = i + 1;		y[count] = j + 1;
				if (is_OK(x[0], y[0], count, x[count], y[count])) count++;
				else continue;

				if (count == 2)
				{
					if (x[0] == x[1] && y[0] == y[1])
					{
						count--;
					}
					else
					{
						domymove(x, y, cnt);
						return;
					}
				}
			}
				
		}
	}



		////////////////////////////////공격///////////////////////////////////////

	static int add_weight = 3;//여기놓으면 4개일때 가산
	int attack1[][6] = {
		{ 1, 1, 1, 0, 0, 0 },			// 1
		{ 0, 1, 1, 1, 0, 0 },			// 2
		{ 0, 0, 1, 1, 1, 0 },			// 3
		{ 0, 0, 0, 1, 1, 1 },			// 4
		{ 1, 0, 1, 1, 0, 0 },			// 5
		{ 0, 1, 0, 1, 1, 0 },			// 6
		{ 0, 0, 1, 0, 1, 1 },			// 7
		{ 1, 1, 0, 1, 0, 0 },			// 8
		{ 0, 1, 1, 0, 1, 0 },			// 9
		{ 0, 0, 1, 1, 0, 1 },			//10
		{ 1, 0, 1, 0, 1, 0 },			//11
		{ 0, 1, 0, 1, 0, 1 },			//12
		{ 1, 0, 0, 1, 1, 0 },			//13
		{ 0, 1, 0, 0, 1, 1 },			//14
		{ 1, 0, 0, 0, 1, 1 },			//15
		{ 1, 1, 0, 0, 1, 0 },			//16
		{ 0, 1, 1, 0, 0, 1 },			//17
		{ 1, 1, 0, 0, 0, 1 },			//18
		{ 1, 0, 1, 0, 0, 1 },			//19
		{ 1, 0, 0, 1, 0, 1 },			//20

		{ 1, 1, 0, 0, 0, 0 },			// 1
		{ 0, 1, 1, 0, 0, 0 },			// 2
		{ 0, 0, 1, 1, 0, 0 },			// 3
		{ 0, 0, 0, 1, 1, 0 },			// 4
		{ 0, 0, 0, 0, 1, 1 },			// 5
		{ 1, 0, 1, 0, 0, 0 },			// 6
		{ 0, 1, 0, 1, 0, 0 },			// 7
		{ 0, 0, 1, 0, 1, 0 },			// 8
		{ 0, 0, 0, 1, 0, 1 },			// 9
		{ 1, 0, 0, 1, 0, 0 },			//10
		{ 0, 1, 0, 0, 1, 0 },			//11
		{ 0, 0, 1, 0, 0, 1 },			//12
		{ 1, 0, 0, 0, 1, 0 },			//13
		{ 0, 1, 0, 0, 0, 1 },			//14
		{ 1, 0, 0, 0, 0, 1 }			//15
	};
	
	int weight[19][19][9] = { 0 };//가중치

	if (count == 0)
	{//돌 두개 놓을 수 있을 때
		for (l = 10; l < 17; l++)
		{
			if (l == 14)
			{
				continue;
			}
			//가로
			for (i = 0; i < 14; i++)
			{
				for (j = 0; j < 19; j++)
				{
					for (k = 0; k < 6; k++)
					{
						search[k] = myBoard(x[0], y[0], count, i + k, j);
						if (search[k] == 3)
							search[k] = 1;
					}

					if (Arr_Equal(search, attack1[l]))
					{
						if (yeo5(i, j, 101 + l, x, y))
						{
							domymove(x, y, cnt);
							return;
						}
					}
				}
			}

			//세로
			for (i = 0; i < 19; i++)
			{
				for (j = 0; j < 14; j++)
				{
					for (k = 0; k < 6; k++)
					{
						search[k] = myBoard(x[0], y[0], count, i, j + k);
						if (search[k] == 3)
							search[k] = 1;
					}

					if (Arr_Equal(search, attack1[l]))
					{
						if (yeo5(i, j, 201 + l, x, y))
						{
							domymove(x, y, cnt);
							return;
						}
					}
				}
			}

			//오른쪽 대각선
			for (i = 0; i < 14; i++)
			{
				for (j = 0; j < 14; j++)
				{
					for (k = 0; k < 6; k++)
					{
						search[k] = myBoard(x[0], y[0], count, i + k, j + k);
						if (search[k] == 3)
							search[k] = 1;
					}

					if (Arr_Equal(search, attack1[l]))
					{
						if (yeo5(i, j, 301 + l, x, y))
						{
							domymove(x, y, cnt);
							return;
						}
					}
				}
			}

			//왼쪽 대각선
			for (i = 5; i < 19; i++)
			{
				for (j = 0; j < 14; j++)
				{
					for (k = 0; k < 6; k++)
					{
						search[k] = myBoard(x[0], y[0], count, i - k, j + k);
						if (search[k] == 3)
							search[k] = 1;
					}

					if (Arr_Equal(search, attack1[l]))
					{
						if (yeo5(i, j, 401 + l, x, y))
						{
							domymove(x, y, cnt);
							return;
						}
					}
				}
			}
		}
	}
	while (count < cnt)
	{
		clear_weight(weight);
		
		for (l = 0; l < 35; l++)
		{
			//가로
			for (i = 0; i < 14; i++)
			{
				for (j = 0; j < 19; j++)
				{
					for (k = 0; k < 6; k++)
					{
						search[k] = myBoard(x[0], y[0], count, i + k, j);
						if (search[k] == 3)
							search[k] = 1;
					}

					if (Arr_Equal(search, attack1[l]))
					{
						
						weight_handling(i, j, 101 + l, weight);
					}
				}
			}

			//세로
			for (i = 0; i < 19; i++)
			{
				for (j = 0; j < 14; j++)
				{
					for (k = 0; k < 6; k++)
					{
						search[k] = myBoard(x[0], y[0], count, i, j + k);
						if (search[k] == 3)
							search[k] = 1;
					}

					if (Arr_Equal(search, attack1[l]))
					{
						weight_handling(i, j, 201 + l, weight);
					}
				}
			}

			//오른쪽 대각선
			for (i = 0; i < 14; i++)
			{
				for (j = 0; j < 14; j++)
				{
					for (k = 0; k < 6; k++)
					{
						search[k] = myBoard(x[0], y[0], count, i + k, j + k);
						if (search[k] == 3)
							search[k] = 1;
					}

					if (Arr_Equal(search, attack1[l]))
					{
						weight_handling(i, j, 301 + l, weight);
					}
				}
			}

			//왼쪽 대각선
			for (i = 5; i < 19; i++)
			{
				for (j = 0; j < 14; j++)
				{
					for (k = 0; k < 6; k++)
					{
						search[k] = myBoard(x[0], y[0], count, i - k, j + k);
						if (search[k] == 3)
							search[k] = 1;
					}

					if (Arr_Equal(search, attack1[l]))
					{
						weight_handling(i, j, 401 + l, weight);
					}
				}
			}
		}
		
		int max_weight[3] = {0, 0, 0};

		for (i = 0; i < 19; i++)
		{
			for (j = 0; j < 19; j++)
			{
				for (k = 0; k < 8; k++)
				{
					if (k < 4)
						weight[i][j][8] += (add_weight * weight[i][j][k]);////////////////////////여기가중치바꾸면대
					else
						weight[i][j][8] += weight[i][j][k];
				}
				for (k = 0; k < 8; k++)
				{
					if (k < 4 && weight[i][j][k])
						weight[i][j][8] *= 10;////////////////////////여기가중치바꾸면대
					else if (k > 3 && weight[i][j][k])
						weight[i][j][8] *= 4;/////////////////////////여기가중치바꾸면대
				}

				if ((max_weight[2] < weight[i][j][8]) )
				{
					max_weight[0] = i;
					max_weight[1] = j;
					max_weight[2] = weight[i][j][8];
				}
			}
		}
		int flag = 0;
		if (max_weight[2] > 0)
		{
			x[count] = max_weight[0];
			y[count] = max_weight[1];
			count++;
			flag = 1;

			if (count == 2)
			{
				if (x[0] == x[1] && y[0] == y[1])
				{
					count--;
				}
				else
				{
					domymove(x, y, cnt);
					return;
				}
			}
		}
		else
		{
			for (i = 0; i < 19; i++)
			{
				for (j = 0; j < 19; j++)
				{
					k = 0;
					if (1 == myBoard(x[0], y[0], count, i, j))
					{
						do {
							x[count] = i + ((rand() % 2) ? -1 : 1);
							y[count] = j + ((rand() % 2) ? -1 : 1);
							k++;
							if (k > 20)
								break;
						} while (!isFree(x[count], y[count]));
					}
					else if (3 == myBoard(x[0], y[0], count, i, j))
					{
						do {
							x[count] = i + ((rand() % 2) ? -1 : 1);
							y[count] = j + ((rand() % 2) ? -1 : 1);
							k++;
							if (k > 20)
								break;
						} while (!isFree(x[count], y[count]));
					}
					else if (2 == myBoard(x[0], y[0], count, i, j))
					{
						do {
							x[count] = i + ((rand() % 2) ? -1 : 1);
							y[count] = j + ((rand() % 2) ? -1 : 1);
							k++;
							if (k > 20)
								break;
						} while (!isFree(x[count], y[count]));
					}
					if ((k < 18) && (k > 0) && is_OK(x[0], y[0], count, x[count], y[count]))
					{
						count++;
						if (count == 2)
						{
							if (x[0] == x[1] && y[0] == y[1])
							{
								count--;
							}
							else
							{
								domymove(x, y, cnt);
								return;
							}
						}
						flag = 2;
					}
				}
			}
		}
		
		if (flag == 0)
		{
			do {
				x[count] = rand() % width;
				y[count] = rand() % height;
			} while (!(isFree(x[count], y[count]) && is_OK(x[0], y[0], count, x[count], y[count])));
			
			count++;

			if (count == 2)
			{
				if (x[0] == x[1] && y[0] == y[1])
				{
					count--;
				}
				else
				{
					domymove(x, y, cnt);
					return;
				}
			}
		}
	}


	////////////////////////////////////////////////////////////////////// 지워야함
	/*
	for (int i = count; i < cnt; i++) {
		do {
			x[i] = rand() % width;
			y[i] = rand() % height;
			if (terminateAI) return;
		} while (!isFree(x[i], y[i]));

		if (x[1] == x[0] && y[1] == y[0]) i--;
	}*/

	// 이 부분에서 자신이 놓을 돌을 출력하십시오.
	// 필수 함수 : domymove(x배열,y배열,배열크기)
	// 여기서 배열크기(cnt)는 myturn()의 파라미터 cnt를 그대로 넣어야합니다.
	//domymove(x, y, cnt);
}

int AWin_case(int s[6])
{
	if (s[0] == 1 && s[1] == 1 && s[2] == 1 && s[3] == 1 && s[4] == 0 && s[5] == 0)		//111100
		return 1;

	if (s[0] == 0 && s[1] == 1 && s[2] == 1 && s[3] == 1 && s[4] == 1 && s[5] == 0)		//011110
		return 2;

	if (s[0] == 0 && s[1] == 0 && s[2] == 1 && s[3] == 1 && s[4] == 1 && s[5] == 1)		//001111
		return 3;

	if (s[0] == 1 && s[1] == 0 && s[2] == 1 && s[3] == 1 && s[4] == 1 && s[5] == 0)		//101110
		return 4;

	if (s[0] == 0 && s[1] == 1 && s[2] == 0 && s[3] == 1 && s[4] == 1 && s[5] == 1)		//010111
		return 5;

	if (s[0] == 1 && s[1] == 0 && s[2] == 0 && s[3] == 1 && s[4] == 1 && s[5] == 1)		//100111
		return 6;

	if (s[0] == 1 && s[1] == 1 && s[2] == 0 && s[3] == 1 && s[4] == 1 && s[5] == 0)		//110110
		return 7;

	if (s[0] == 0 && s[1] == 1 && s[2] == 1 && s[3] == 0 && s[4] == 1 && s[5] == 1)		//011011
		return 8;

	if (s[0] == 1 && s[1] == 1 && s[2] == 0 && s[3] == 0 && s[4] == 1 && s[5] == 1)		//110011
		return 9;

	if (s[0] == 1 && s[1] == 1 && s[2] == 1 && s[3] == 0 && s[4] == 1 && s[5] == 0)		//111010
		return 10;

	if (s[0] == 0 && s[1] == 1 && s[2] == 1 && s[3] == 1 && s[4] == 0 && s[5] == 1)		//011101
		return 11;

	if (s[0] == 1 && s[1] == 1 && s[2] == 1 && s[3] == 0 && s[4] == 0 && s[5] == 1)		//111001
		return 12;

	if (s[0] == 1 && s[1] == 1 && s[2] == 1 && s[3] == 1 && s[4] == 1 && s[5] == 0)		//111110
		return 13;

	if (s[0] == 0 && s[1] == 1 && s[2] == 1 && s[3] == 1 && s[4] == 1 && s[5] == 1)		//011111
		return 14;

	if (s[0] == 1 && s[1] == 0 && s[2] == 1 && s[3] == 1 && s[4] == 1 && s[5] == 1)		//101111
		return 15;

	if (s[0] == 1 && s[1] == 1 && s[2] == 0 && s[3] == 1 && s[4] == 1 && s[5] == 1)		//110111
		return 16;

	if (s[0] == 1 && s[1] == 1 && s[2] == 1 && s[3] == 0 && s[4] == 1 && s[5] == 1)		//111011
		return 17;

	if (s[0] == 1 && s[1] == 1 && s[2] == 1 && s[3] == 1 && s[4] == 0 && s[5] == 1)		//111101
		return 18;

	if (s[0] == 1 && s[1] == 1 && s[2] == 0 && s[3] == 1 && s[4] == 0 && s[5] == 1)		//110101
		return 19;

	if (s[0] == 1 && s[1] == 0 && s[2] == 1 && s[3] == 1 && s[4] == 0 && s[5] == 1)		//101101
		return 20;

	if (s[0] == 1 && s[1] == 0 && s[2] == 1 && s[3] == 0 && s[4] == 1 && s[5] == 1)		//101011
		return 21;

	return 0;
}

int Arr_Equal(int s[6], int p[6])
{
	return (s[0] == p[0] && s[1] == p[1] && s[2] == p[2] && s[3] == p[3] && s[4] == p[4] && s[5] == p[5]);
}

int is_OK(int my_x, int my_y, int count, int x, int y)
{
	int i, j, k;
	int a[7];

	for (i = Max(x - 6, 0); i <= Min(x, 12) ; i++)
	{
		for (k = 0; k < 7; k++)
		{
			a[k] = myBoard(my_x, my_y, count, i + k, y);

			if (i + k == x)
				a[k] = 1;

			if (a[k] == 3)
				a[k] = 1;
		}

		if (a[0] == 1 && a[1] == 1 && a[2] == 1 && a[3] == 1 && a[4] == 1 && a[5] == 1 && a[6] == 1)
			return 0;
	}

	for (i = Max(y - 6, 0); i <= Min(y, 12); i++)
	{
		for (k = 0; k < 7; k++)
		{
			a[k] = myBoard(my_x, my_y, count, x, i + k);

			if (i + k == y)
				a[k] = 1;

			if (a[k] == 3)
				a[k] = 1;
		}

		if (a[0] == 1 && a[1] == 1 && a[2] == 1 && a[3] == 1 && a[4] == 1 && a[5] == 1 && a[6] == 1)
			return 0;
	}

	if (x > y)
	{
		for (j = Max(y - 6, 0), i = x - (y - j); i <= Min(x, 12); i++, j++)
		{
			for (k = 0; k < 7; k++)
			{
				a[k] = myBoard(my_x, my_y, count, i + k, j + k);

				if (i + k == x && j + k == y)
					a[k] = 1;

				if (a[k] == 3)
					a[k] = 1;
			}

			if (a[0] == 1 && a[1] == 1 && a[2] == 1 && a[3] == 1 && a[4] == 1 && a[5] == 1 && a[6] == 1)
				return 0;
		}

		for(i = Min(x + 6, 12), j = y - (i - x); j <= Min(y, 12); i--, j++)
		{
			for (k = 0; k < 7; k++)
			{
				a[k] = myBoard(my_x, my_y, count, i - k, j + k);

				if (i - k == x && j + k == y)
					a[k] = 1;

				if (a[k] == 3)
					a[k] = 1;
			}

			if (a[0] == 1 && a[1] == 1 && a[2] == 1 && a[3] == 1 && a[4] == 1 && a[5] == 1 && a[6] == 1)
				return 0;
		}
	}
	else
	{
		for (i = Max(x - 6, 0), j = y - (x - i); j <= Min(y, 12); i++, j++)
		{
			for (k = 0; k < 7; k++)
			{
				a[k] = myBoard(my_x, my_y, count, i + k, j + k);

				if (i + k == x && j + k == y)
					a[k] = 1;

				if (a[k] == 3)
					a[k] = 1;
			}

			if (a[0] == 1 && a[1] == 1 && a[2] == 1 && a[3] == 1 && a[4] == 1 && a[5] == 1 && a[6] == 1)
				return 0;
		}

		for (j = Max(y - 6, 0), i = x + (y - j); i >= Min(y, 12); i--, j++)
		{
			for (k = 0; k < 7; k++)
			{
				a[k] = myBoard(my_x, my_y, count, i - k, j + k);

				if (i - k == x && j + k == y)
					a[k] = 1;

				if (a[k] == 3)
					a[k] = 1;
			}

			if (a[0] == 1 && a[1] == 1 && a[2] == 1 && a[3] == 1 && a[4] == 1 && a[5] == 1 && a[6] == 1)
				return 0;
		}
	}

	return 1;
}

int Max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int Min(int a, int b)
{
	if (a < b)
		return a;
	else
		return b;
}

int myBoard(int my_x, int my_y, int count, int x, int y)
{
	if (count == 1 && my_x == x && my_y == y)
	{
		return 1;
	}
	return showBoard(x, y);
}

int Cross_4(int x, int y)
{
	int i, j, k;
	int num = 0;
	int a[4];

	for (i = Max(x - 3, 0); i <= Min(x, 15); i++)
	{
		for (k = 0; k < 4; k++)
		{
			a[k] = showBoard(i + k, y);

			if (i + k == x)
				a[k] = 2;

			if (a[k] == 3)
				a[k] = 2;
		}

		if (a[0] == 2 && a[1] == 2 && a[2] == 2 && a[3] == 2)
			num++;
	}

	for (i = Max(y - 3, 0); i <= Min(y, 15); i++)
	{
		for (k = 0; k < 4; k++)
		{
			a[k] = showBoard(x, i + k);

			if (i + k == y)
				a[k] = 2;

			if (a[k] == 3)
				a[k] = 2;
		}

		if (a[0] == 2 && a[1] == 2 && a[2] == 2 && a[3] == 2)
			num++;
	}

	if (x > y)
	{
		for (j = Max(y - 3, 0), i = x - (y - j); i <= Min(x, 15); i++, j++)
		{
			for (k = 0; k < 4; k++)
			{
				a[k] = showBoard(i + k, j + k);

				if (i + k == x && j + k == y)
					a[k] = 2;

				if (a[k] == 3)
					a[k] = 2;
			}

			if (a[0] == 2 && a[1] == 2 && a[2] == 2 && a[3] == 2)
				num++;
		}

		for (i = Min(x + 3, 15), j = y - (i - x); j <= Min(y, 15); i--, j++)
		{
			for (k = 0; k < 4; k++)
			{
				a[k] = showBoard(i - k, j + k);

				if (i - k == x && j + k == y)
					a[k] = 2;

				if (a[k] == 3)
					a[k] = 2;
			}

			if (a[0] == 2 && a[1] == 2 && a[2] == 2 && a[3] == 2)
				num++;
		}
	}
	else
	{
		for (i = Max(x - 3, 0), j = y - (x - i); j <= Min(y, 15); i++, j++)
		{
			for (k = 0; k < 4; k++)
			{
				a[k] = myBoard(my_x, my_y, count, i + k, j + k);

				if (i + k == x && j + k == y)
					a[k] = 2;

				if (a[k] == 3)
					a[k] = 2;
			}

			if (a[0] == 2 && a[1] == 2 && a[2] == 2 && a[3] == 2)
				num++;
		}

		for (j = Max(y - 3, 0), i = x + (y - j); i >= Min(y, 15); i--, j++)
		{
			for (k = 0; k < 4; k++)
			{
				a[k] = myBoard(my_x, my_y, count, i - k, j + k);

				if (i - k == x && j + k == y)
					a[k] = 2;

				if (a[k] == 3)
					a[k] = 2;
			}

			if (a[0] == 2 && a[1] == 2 && a[2] == 2 && a[3] == 2)
				num++;
		}
	}

	return num;
}