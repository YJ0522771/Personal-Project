package 프로젝트_슈팅게임;

import javax.swing.ImageIcon;

public class FinalEnemy extends Enemy			//게임 종료 40초 전에 등장하는 enemy
{
	private static ImageIcon img = new ImageIcon("image/FINAL.jpg");
	private static final int life = 50;			//final enemy가 몇 번 총알을 맞아야 소멸되는지를 나타냄
	private static boolean First = true;		//해당 enemy 인스턴스가 이미 만들어진 적이 있는지를 나타냄 true면 아직 만들어진 적이 없다는 의미
	
	public FinalEnemy()
	{
		super(img);
		First = false;		//해당 enemy가 생성되었으므로 처음이 아님을 설정
	}
	
	public boolean death()		//해당 enemy가 소멸해야하는지 여부를 나타냄
	{
		if(super.getCount() >= this.life)	//총을 life이상으로 맞으면 소멸해야함을 알림
			return true;
		else
			return false;
	}
	
	public static boolean isFirst()		//해당 enemy의 인스턴스의 생성이 처음인지 아닌지를 반환
	{
		return First;
	}

}
