package 프로젝트_슈팅게임;
import javax.swing.*;

public class Enemy extends JLabel		//enemy 클래스 //mid enemy와 final enemy의 super class
{
	private int count = 0;				//총알을 몇 번 맞았는지 세는 변수
	private int direct = -1; 			//해당 enemy의 이동 방향
	private int velocity = 8;			//move 메소드가 호출될 때마다 움직이는 거리
	
	
	public Enemy(ImageIcon img)
	{
		super(img);
		super.setLocation(600, 0);
		super.setSize(60, 90);
	}
	
	public void move()
	{
		if(direct == 1)		//오른쪽으로 이동
			setLocation(this.getLocation().x + velocity, this.getLocation().y);
		else if(direct == -1)		//왼쪽으로 이동
			setLocation(this.getLocation().x - velocity, this.getLocation().y);
		
		if(this.getLocation().x >= 490)		//enemy가 화면을 벗어나면 이동 방향을 바꾼다
			direct = -1;
		else if(this.getLocation().x <= 0)
			direct = 1;
	}
	
	public void shotByBullet()		//총알을 맞았을 때 count를 증가시켜준다
	{
		count++;
	}
	
	public int getCount()			//총알을 몇 번 맞았는지를 반환
	{
		return this.count;
	}
	

}
