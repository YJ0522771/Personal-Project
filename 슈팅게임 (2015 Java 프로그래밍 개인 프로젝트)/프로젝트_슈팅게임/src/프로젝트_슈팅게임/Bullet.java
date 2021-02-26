package 프로젝트_슈팅게임;
import javax.swing.*;
import java.awt.*;

public class Bullet extends JLabel		//총알 클래스
{
	private int velocity = 10;		//move 메소드가 한 번 호출 될 때마다 총알이 움직이는 거리
	private static ImageIcon img = new ImageIcon("image/bullet.jpg");	//총알 이미지
	private boolean visible = false;		//현재 해당 총알이 화면에 비춰지고 있어야 하는 상태인지 알려줌
	
	public Bullet(Point us)
	{
		super(img);
		super.setSize(4,4);
		visible = true;						//화면에 생성되었으므로 visiable 변수를 true로 한다
		super.setLocation(us.x+17, us.y);		//플레이어의 중앙에서 총알이 발사되도록 한다
	}
	
	public void move()
	{
		setLocation(this.getX(), this.getY() - velocity);	//초기 위치에서 위쪽으로만 이동
		
		if(this.getY() < 0)
		{
			visible = false;		//총알이 화면 끝까지 날아가면 더이상 화면에 보일 필요가 없음을 설정
		}
	}
	
	public boolean isvisible()
	{
		return visible;			//현지 총알이 보여져야하는 상태인지 아닌지를 알기위해
	}								//visiable을 반환하는 함수

}
