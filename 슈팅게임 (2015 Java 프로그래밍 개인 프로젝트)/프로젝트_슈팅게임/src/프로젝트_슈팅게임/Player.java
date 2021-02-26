package 프로젝트_슈팅게임;
import javax.swing.*;

public class Player extends JLabel
{
	private int totalscore;		//플레이어의 최종스코어
	private String name;		//이름
	private char grade;			//최종스코어에 따른 grade
	private static ImageIcon user = new ImageIcon("image/player.png");
	private final int SCORE_A = 2;		//각 item에 따른 획득 점수
	private final int SCORE_B = 1;
	private final int SCORE_C = -1;
	private final int SCORE_D = -2;
	private final int SCORE_MID = 20;	//enemy를 잡았을 경우 얻는 점수
	private final int SCORE_FINAL = 40;
	
	public Player(String name)
	{
		super(user);
		super.setSize(40, 40);
		this.totalscore = 0;		//스코어 초기화
		this.name = name;			//넘겨받은 이름을 플레이어 이름으로 설정
	}
	
	public void scoreCalculate(char event)		//각 item별 점수 계산 메소드
	{
		if(event == 'A')
			this.totalscore += SCORE_A;
		else if(event == 'B')
			this.totalscore += SCORE_B;
		else if(event == 'C')
			this.totalscore += SCORE_C;
		else if(event == 'D')
			this.totalscore += SCORE_D;
		else if(event == 'F')
			this.totalscore = 0;
		else if(event == 'M')
			this.totalscore += SCORE_MID;
		else if(event == 'T')
			this.totalscore += SCORE_FINAL;
	}
	
	public int getTotal()		//최종 스코어 반환
	{
		return this.totalscore;
	}
	
	public String getName()		//이름 반환
	{
		return this.name;
	}
	
	public void setGrade()		//최종 스코어에 따른 grade 반환
	{
		if(this.totalscore >= 160)
			this.grade = 'A';
		else if(this.totalscore >= 120)
			this.grade = 'B';
		else if(this.totalscore >= 80)
			this.grade = 'C';
		else if(this.totalscore >= 40)
			this.grade = 'D';
		else
			this.grade = 'F';
	}
	
	public char getGrade()		//grade 반환
	{
		return this.grade;
	}
}
