package 프로젝트_슈팅게임;
import javax.swing.*;
import java.security.SecureRandom;

public class Items extends JLabel		//item(탄막) 클래스
{
	private static final char[] labels = {'A', 'B', 'C', 'D', 'F'};		//모든 item 인스턴스에 사용되는 index별 마크
	private static ImageIcon[] imgs = new ImageIcon[5];					//랜덤으로 결정되는 index에 의해 이미지가 결정되므로 각각의 이미지 인스턴스를 배열로 만듬
	private int index;				//인스턴스 생성과 함께 랜덤으로 결정되는 수
	private int velocity = 0;		//인스턴스 생성과 함께 랜덤으로 결정
	
	private boolean visible = false;		//현재 해당 item이 보여져야하는 상황인지 나타냄
	
	private SecureRandom rand = new SecureRandom();
	
	
	public Items(int random)
	{
		super(imgs[random]);	//인스턴스 생성 시 랜덤으로 받은 수를 index로 결정하고 해당 이미지를 넣어 인스턴스 생성
		this.index = random;	
		this.velocity = rand.nextInt(3)+1;	//속도를 1~3 중 랜덤으로 결정
		setSize(20,20);
		setLocation(rand.nextInt(570), 0);	//내려오는 초기 x좌표도 랜덤으로 결정
		visible = true;					//현재 해당 item이 화면에 보여져야 함을 나타냄
	}
	
	public static void initialize()			//이미지 배열을 초기화하는 static메소드
	{
		imgs[0] = new ImageIcon("image/A.png");
		imgs[1] = new ImageIcon("image/B.png");
		imgs[2] = new ImageIcon("image/C.png");
		imgs[3] = new ImageIcon("image/D.png");
		imgs[4] = new ImageIcon("image/F.png");
	}
	
	public void move()
	{
		setLocation(this.getX(), this.getY()+velocity);
		
		if(this.getY() > 750)			//item이 화면 맨 밑까지 내려가면 화면에 보여지지 말아야함을 알림
		{
			visible = false;
		}
	}
	
	public boolean isvisible()			//현재 화면에 보여야하는 상태인지를 반환
	{
		return visible;
	}
	
	public char getLabel()				//해당 인스턴스가 어떤 마크인지 index에 해당하는 마크를 반환
	{
		return labels[index];
	}

}
