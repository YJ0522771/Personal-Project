package 프로젝트_슈팅게임;
import java.awt.*;
import java.awt.event.*;
import java.security.SecureRandom;
import javax.swing.*;
import java.util.concurrent.*;
import java.util.*;

public class PlayGameFrame extends JFrame
{
	private JPanel userPlay = new JPanel();			//플레이어가 움직이는 panel
	private JPanel bulletPanel = new JPanel();		//총알이 움직이는 panel
	private JPanel itemMove = new JPanel();			//item이 움직이는 panel
	private JPanel enemyMove = new JPanel();		//enemy가 움직이는 panel
	private PlayPanel mainPlay = new PlayPanel();	//배경 이미지가 있는 panel
	private JPanel state = new JPanel();			//점수, 이름 , 시간이 표시되는 곳의 panel
	private JLabel scorefield;		//점수 표시 영역
	private JLabel namefield;		//이름 표시 영역
	private JLabel timefield;		//시간 표시 영역
	
	private Player user;		//플레이어
	private int user_v = 4;		//플레이어 속도
	private boolean[] keys = {false, false, false, false}; //L, R, U, D 각 방향키가 눌려진 상태인지를 나타냄
	private ArrayList<Bullet> bullets = new ArrayList<Bullet>();	//생성된 총알 리스트
	
	private MidEnemy me;		//mid enemy
	private FinalEnemy fe;		//final enemy
	
	private ArrayList<Items> items = new ArrayList<Items>();		//item 리스트
	private ArrayList<Items> item_mes = new ArrayList<Items>();		//enemy가 뿌리는 item 리스트
	private ArrayList<Items> item_fes = new ArrayList<Items>();
	
	private int time = 120;			//플레이 타임
	
	private SecureRandom rand = new SecureRandom();
	
	private Object key_i = new Object();		//동기화를 위한 key
	private Object key_mes = new Object();
	private Object key_fes = new Object();
	private Object key_b = new Object();
	
	private PlayGameFrame this_s = this;		//this 포인터

	
	
	
	public PlayGameFrame(String name)
	{
		setTitle("Shooting Game");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		user = new Player(name);
		
		this.setLayout(null);			//좌표로 component를 붙이기 위해 레이아웃을 null로 설정
		this.setSize(4*150, 5*150);
		
		scorefield = new JLabel("Score : " + user.getTotal());		//점수, 이름, 시간 표시 label 생성
		namefield = new JLabel("Name : " + user.getName());
		timefield = new JLabel("Time : " + time);
		
		Font font = new Font("", Font.ITALIC, 20);			//점수, 이름, 시간의 폰트 설정
		scorefield.setFont(font);
		namefield.setFont(font);
		timefield.setFont(font);
		
		state.setBackground(Color.MAGENTA);			//점수, 이름, 시간을 표시하는 panel의 배경색 설정
		state.setLayout(new GridLayout(1,3));		//grid 레이아웃으로 세 칸으로 나눈 뒤
		state.add(scorefield);						//각 칸마다 점수, 이름, 시간을 추가
		state.add(namefield);
		state.add(timefield);
		state.setSize(this.getWidth(), this.getHeight()/15);
		state.setLocation(0, 0);
		
		add(state);
		
		mainPlay.setLayout(null);
		mainPlay.setLocation(0, state.getHeight());
		mainPlay.setSize(this.getWidth(), this.getHeight()-state.getHeight());
		
		userPlay.setLayout(null);
		userPlay.setLocation(0, 0);
		userPlay.setSize(this.getWidth(), this.getHeight()-state.getHeight());
		userPlay.setOpaque(false);			//panel의 배경을 투명하게 함
		user.setLocation((this.getWidth()-user.getWidth())/2, userPlay.getHeight() - 2*user.getHeight());	//플레이어의 초기 위치를 화면 맨 아래 가운데로 설정
		userPlay.add(user);		
		
		itemMove.setLayout(null);
		itemMove.setLocation(0, 0);
		itemMove.setSize(this.getWidth(), this.getHeight()-state.getHeight());
		itemMove.setOpaque(false);			//panel의 배경을 투명하게 함
		
		bulletPanel.setLayout(null);
		bulletPanel.setLocation(0, 0);
		bulletPanel.setSize(this.getWidth(), this.getHeight()-state.getHeight());
		bulletPanel.setOpaque(false);		//panel의 배경을 투명하게 함
		
		enemyMove.setLayout(null);
		enemyMove.setLocation(0, 0);
		enemyMove.setSize(this.getWidth(), this.getHeight()-state.getHeight());
		enemyMove.setOpaque(false);			//panel의 배경을 투명하게 함
		
		mainPlay.add(itemMove);			//투명한 panel들을 배경 이미지 패널 위에 덧씌움
		itemMove.add(bulletPanel);
		bulletPanel.add(enemyMove);
		enemyMove.add(userPlay);
		
		add(mainPlay);
		

		
		Timer timer = new Timer();					//Runnable을 상속한 각각 쓰레드의 인스턴스 생성
		MovingPlayer player = new MovingPlayer();
		MovingItems moving = new MovingItems();
		InitialItems initial = new InitialItems();
		MovingBullet moveBullet = new MovingBullet();
		MovingEnemy enemy = new MovingEnemy();
		
		ExecutorService ex = Executors.newCachedThreadPool();
		ex.execute(timer);			//쓰레드 실행
		ex.execute(player);
		ex.execute(moving);
		ex.execute(initial);
		ex.execute(moveBullet);
		ex.execute(enemy);
		
		setVisible(true);
	
		
		userPlay.requestFocus();							//키 조작을 위해 포커스를 얻음
		userPlay.addKeyListener(new MovingListener());		//플레이어의 키조작 listener 추가
		
	}
	
	public class MovingListener extends KeyAdapter		//플레이어 이동 listener
	{
		public void keyPressed(KeyEvent e)
		{
			if(e.getKeyCode() == KeyEvent.VK_LEFT)		//방향키가 눌려졌을 때 키가 눌러져있음을 알리는 변수를 true로 바꿈
			{
				keys[0] = true;
			}
			else if(e.getKeyCode() == KeyEvent.VK_RIGHT)
			{
				keys[1] = true;
			}
			if(e.getKeyCode() == KeyEvent.VK_UP)
			{
				keys[2] = true;
			}
			else if(e.getKeyCode() == KeyEvent.VK_DOWN)
			{
				keys[3] = true;
			}
			
			if(e.getKeyChar() == ' ')		//스페이스 바가 눌려지면 총알 발사
			{
				int next;
				synchronized(key_b)
				{
					next = bullets.size();
					Bullet temp = new Bullet(user.getLocation());		//총알 인스턴스 생성
					bullets.add(temp);
					bulletPanel.add(bullets.get(next));					//panel에 추가
				}
			}
		}
		
		public void keyReleased(KeyEvent e)
		{
			if(e.getKeyCode() == KeyEvent.VK_LEFT)					//방향키에서 손을 떼면 false로 바뀜
			{
				keys[0] = false;
			}
			else if(e.getKeyCode() == KeyEvent.VK_RIGHT)
			{
				keys[1] = false;
			}
			if(e.getKeyCode() == KeyEvent.VK_UP)
			{
				keys[2] = false;
			}
			else if(e.getKeyCode() == KeyEvent.VK_DOWN)
			{
				keys[3] = false;
			}
		}
		
	}
	
	public class Timer implements Runnable		//타이머 쓰레드
	{
		public void run()
		{
			while(true)
			{
				try 
				{
					Thread.sleep(1000);
				}
				catch(InterruptedException e) 
				{
					return;
				}
				
				time--;
				timefield.setText("Time : " + time);
				
				if(time == 0)			//플레이 타임이 끝나면 
				{
					try 
					{
						Thread.sleep(2000);			//2초 딜레이
					}
					catch(InterruptedException e) 
					{
						return;
					}
					
					break;			//반복문 탈출로 쓰레드 종료
				}
					
			}
			
			new Record(user);		//기록을 파일에 저장
			user.setGrade();		//최종 스코어를 통해 grade 설정
			this_s.setVisible(false);			//플레이 화면을 지움
			new GradeFrame(user.getGrade());	//grade를 나타내는 화면을 불러옴
			
		}

	}
	
	public class MovingPlayer implements Runnable	//플레이어의 움직임에 대한 쓰레드
	{
		public void run()
		{
			while(true)
			{
				try 
				{
					Thread.sleep(15);
				}
				catch(InterruptedException e) 
				{
					return;
				}
				
				Point p = user.getLocation();
				
				if(keys[0])		//왼쪽 키가 눌려있으면 왼쪽으로 이동
				{
					if(p.x > 0)
					{
						user.setLocation(p.x - user_v, p.y);
					}
		
				}
				else if(keys[1])	//오른쪽 키가 눌려있으면 오른쪽으로 이동
				{
					if(p.x < 545)
					{
						user.setLocation(p.x + user_v, p.y);
					}
				}
				if(keys[2])		//위쪽 키가 눌려있으면 위로 이동
				{
					if(p.y > 0)
					{
						user.setLocation(p.x, p.y - user_v);
					}
				}
				else if(keys[3])	//아래쪽 키가 눌려있으면 아래로 이동
				{
					if(p.y < 620)
					{
						user.setLocation(p.x, p.y + user_v);
					}
				}
	
				if(time == 0)		//플레이 타임이 끝나면 반복문 탈출, 쓰레드 종료
					break;
			}
		}
	}
	
	public class MovingItems implements Runnable	//item을 움직이는 쓰레드
	{
		public void run()
		{
			while(true)
			{
				try 
				{
					Thread.sleep(15);
				}
				catch(InterruptedException e) 
				{
					return;
				}
				
				for(int i=0; i<items.size(); i++)	//item 리스트에 들어있는 item의 수만큼
				{
					if(items.get(i).isvisible())	//item이 보여져야하는 상황이면 움직임
					{
						items.get(i).move();
					}
					if(!items.get(i).isvisible())	//보이지 말아야하는 상황이면
					{
						itemMove.remove(items.get(i));	//화면과 리스트에서 삭제
						synchronized(key_i)
						{
							items.remove(i);
						}
					}
					
					int itx = items.get(i).getLocation().x + (items.get(i).getWidth()/2);
					int ity = items.get(i).getLocation().y + (items.get(i).getHeight()/2);
					Point us = user.getLocation();
					
					if((itx >= us.x && itx <= us.x+user.getWidth())			//item이 플레이어의 영역안에 들어가면
							&&(ity >= us.y && ity <= us.y+user.getHeight()))
					{
						user.scoreCalculate(items.get(i).getLabel());	//해당 item의 마크에 따라 점수를 증가
						itemMove.remove(items.get(i));		//화면과 리스트에서 삭제
						synchronized(key_i)
						{
							items.remove(i);
						}
						
						scorefield.setText("Score : " + user.getTotal());	//스코어 필드 변경
					}
				}
				
				if(!MidEnemy.isFirst())
				{
					if(!me.death())
					{
						for(int i=0; i<item_mes.size(); i++)		//enemy에 의한 F item의 움직임
						{
							if(item_mes.get(i).isvisible())		//위의 코드와 동일
							{
								item_mes.get(i).move();
							}
							if(!item_mes.get(i).isvisible())
							{
								itemMove.remove(item_mes.get(i));
								synchronized(key_mes)
								{
									item_mes.remove(i);
								}
							}
							
							int itx = item_mes.get(i).getLocation().x + (item_mes.get(i).getWidth()/2);
							int ity = item_mes.get(i).getLocation().y + (item_mes.get(i).getHeight()/2);
							Point us = user.getLocation();
							
							if((itx >= us.x && itx <= us.x+user.getWidth())
									&&(ity >= us.y && ity <= us.y+user.getHeight()))
							{
								user.scoreCalculate(item_mes.get(i).getLabel());
								itemMove.remove(item_mes.get(i));
								synchronized(key_mes)
								{
									item_mes.remove(i);
								}
								
								scorefield.setText("Score : " + user.getTotal());
							}
						}
					}
				}
				
				if(!FinalEnemy.isFirst())
				{
					if(!fe.death())
					{
						for(int i=0; i<item_fes.size(); i++)		//위의 mid enemy와 동일
						{
							if(item_fes.get(i).isvisible())
							{
								item_fes.get(i).move();
							}
							if(!item_fes.get(i).isvisible())
							{
								itemMove.remove(item_fes.get(i));
								synchronized(key_fes)
								{
									item_fes.remove(i);
								}
							}
							
							int itx = item_fes.get(i).getLocation().x + (item_fes.get(i).getWidth()/2);
							int ity = item_fes.get(i).getLocation().y + (item_fes.get(i).getHeight()/2);
							Point us = user.getLocation();
							
							if((itx >= us.x && itx <= us.x+user.getWidth())
									&&(ity >= us.y && ity <= us.y+user.getHeight()))
							{
								user.scoreCalculate(item_fes.get(i).getLabel());
								itemMove.remove(item_fes.get(i));
								synchronized(key_fes)
								{
									item_fes.remove(i);
								}
								
								scorefield.setText("Score : " + user.getTotal());
							}
						}
					}
				}
				
				if(time == 0)			//플레이 타임이 끝나면 
				{
					for(int i=0; i<items.size(); i++)	//화면상으 모든 item을 지우고 
					{
						itemMove.remove(items.get(i));
					}
					
					items.clear();
					
					break;		//쓰레드 종료
				}
			}
		}
		
	}
	
	public class InitialItems implements Runnable		//item 생성 쓰레드
	{
		public void run()
		{
			int next = 0;
			Items temp;
			
			Items.initialize();
			
			while(true)
			{
				synchronized(key_i)
				{
					next = items.size();
					temp = new Items(rand.nextInt(2) + rand.nextInt(2) + rand.nextInt(2));		//ABCD를 각각 1/8, 3/8, 3/8, 1/8의 확률로 생성
					items.add(temp);	//생성한 인스턴스를 리스트에 추가
					itemMove.add(items.get(next));	//화면에 추가
				}
				
				if(!MidEnemy.isFirst())		//mid enemy가 활성화 중일때 F생성
				{
					if(!me.death())
					{
						synchronized(key_mes)
						{
							next = item_mes.size();
							temp = new Items(4);
							temp.setLocation(me.getX() + 30, me.getY() + 45);
							item_mes.add(temp);
							itemMove.add(item_mes.get(next));
						}
					}
				}
				
				if(!FinalEnemy.isFirst())		//final enemy가 활성화 중일때 F생성
				{
					if(!fe.death())
					{
						synchronized(key_fes)
						{
							next = item_fes.size();
							temp = new Items(4);
							temp.setLocation(fe.getX() + 30, fe.getY() + 45);
							item_fes.add(temp);
							itemMove.add(item_fes.get(next));
						}
					}
				}
				
				try 		//0.4초에 한 번씩 item 생성
				{
					Thread.sleep(400);
				}
				catch(InterruptedException e) 
				{
					return;
				}
				
				if(time == 0)		//플레이 타임이 끝나면 쓰레드 종료
					break;
			}
		}
	}
	
	public class MovingBullet implements Runnable		//총알을 움직이는 쓰레드
	{
		public void run()
		{
			while(true)
			{
				try 
				{
					Thread.sleep(15);
				}
				catch(InterruptedException e) 
				{
					return;
				}
				
				for(int i=0; i<bullets.size(); i++)		
				{
					if(bullets.get(i).isvisible())		//총알이 화면에 보여져야 할 때면 움직임
					{
						bullets.get(i).move();
					}
					if(!bullets.get(i).isvisible())	//화면에서 보여지지 말아야하면 
					{
						synchronized(key_b)
						{
							bulletPanel.remove(bullets.get(i));		//화면과 리스트에서 제거
							bullets.remove(i);
						}
					}
				}
				
				for(int i=0; i<bullets.size(); i++)
				{
					int bx = bullets.get(i).getX();
					int by = bullets.get(i).getY();
					
					if(!MidEnemy.isFirst())
					{
						int mx = me.getX();
						int my = me.getY();
						
						if(!me.death())
						{
							if((bx>=mx && bx<=mx+me.getWidth()) 		//총알이 enemy의 영역안에 들어오면
									&& (by>=my && by<=my+me.getHeight()))
							{
								me.shotByBullet();			//총알에 맞았을 때의 메소드 실행
								synchronized(key_b)
								{
									bulletPanel.remove(bullets.get(i));		//총알은 화면과 리스트에서 삭제
									bullets.remove(i);
								}
							}
							
							if(me.death())		//enemy가 죽으면
							{
								enemyMove.remove(me);		//화면에서 enemy 삭제
								
								for(int j=0; j<item_mes.size(); j++)		//화면에서 F를 모두 삭제
								{
									itemMove.remove(item_mes.get(j));
								}
								
								user.scoreCalculate('M');		//해당 에너미의 점수 부여
								scorefield.setText("Score : " + user.getTotal());
							}
						}
						
					}
					
					if(!FinalEnemy.isFirst())		//위의 mid와 동일
					{
						int fx = fe.getX();
						int fy = fe.getY();
						
						if(!fe.death())
						{
							if((bx>=fx && bx<=fx+fe.getWidth()) 
									&& (by>=fy && by<=fy+fe.getHeight()))
							{
								fe.shotByBullet();
								bulletPanel.remove(bullets.get(i));
								bullets.remove(i);
							}
							
							if(fe.death())
							{
								enemyMove.remove(fe);
								
								for(int j=0; j<item_fes.size(); j++)
								{
									itemMove.remove(item_fes.get(j));
								}
								
								user.scoreCalculate('T');
								scorefield.setText("Score : " + user.getTotal());
							}
						}
						
					}
				}
				
				if(time == 0)		//플레이 타임이 끝나면 쓰레드 종료
				{
					if(!MidEnemy.isFirst())
					{
						if(!me.death())
						{
							for(int j=0; j<item_mes.size(); j++)		//화면에서 F를 모두 삭제
							{
								itemMove.remove(item_mes.get(j));
							}
						}	
					}
					
					if(!FinalEnemy.isFirst())
					{
						if(!fe.death())
						{
							for(int j=0; j<item_fes.size(); j++)
							{
								itemMove.remove(item_fes.get(j));
							}
						}
					}
				
					break;
				}
			}
			
			
		}
	}

	public class MovingEnemy implements Runnable		//enemy를 움직이는 쓰레드
	{
		public void run()
		{
			while(true)
			{
				try 
				{
					Thread.sleep(15);
				}
				catch(InterruptedException e) 
				{
					return;
				}
					
				if(time == 80 && MidEnemy.isFirst())	//시간이 80초 남았을 때, mid가 아직 생성된 적이 없으면 생성
				{
					me = new MidEnemy();
					enemyMove.add(me);
				}
				
				if(!MidEnemy.isFirst())		//이미 한번 생성 되었고
				{
					if(!me.death())			//죽지 않았다면
					{
						me.move();			//움직임
					}
				}
				
				if(time == 40 && FinalEnemy.isFirst())		//시간이 40초 남았고, final이 아직 생성된 적이 없으면 생성
				{
					fe = new FinalEnemy();
					enemyMove.add(fe);
				}
				
				if(!FinalEnemy.isFirst())		//위와 동일
				{
					if(!fe.death())
					{
						fe.move();
					}
				}
				
				if(time == 0)
				{
					if(!MidEnemy.isFirst())
					{
						if(!me.death())
						{
							enemyMove.remove(me);
						}
					}
					
					if(!FinalEnemy.isFirst())
					{
						if(!fe.death())
						{
							enemyMove.remove(fe);
						}
					}
					
					break;
				}
			}
		}
	}
}
