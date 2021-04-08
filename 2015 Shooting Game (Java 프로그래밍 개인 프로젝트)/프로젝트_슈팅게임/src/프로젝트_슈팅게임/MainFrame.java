package 프로젝트_슈팅게임;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;

public class MainFrame extends JFrame		//프로그램을 시작하면 나오는 첫화면
{
	private String name;		//사용자로부터 이름을 입력 받을 변수
	private MainPanel bg;		//frame에 panel
	private JButton start;		//game start button
	private JButton record;		//지금까지의 top10기록을 보는 화면으로 가는 button
	private JTextField input;	//이름을 입력할 textfield
	private JFrame main;		//이 프레임의 this 포인터를 저장할 곳
	private JFrame insert;		//이름을 입력 받을 창
	
	public MainFrame()
	{
		setTitle("Shooting Game");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		setSize(4*150, 5*150);
		
		bg = new MainPanel();		//배경 이미지가 붙은 panel
		
		start = new JButton("Start Game");	//우 button의 인스턴스 생성
		record = new JButton("Show Record");
		
		bg.setLayout(null);		//각 component를 좌표값으로 붙이기 위해 레이아웃을 null로 설정
		
		start.setSize(this.getWidth()/3, this.getHeight()/15);		//각 button의 크기와 위치 설정
		start.setLocation((this.getWidth()-start.getWidth())/2-10, this.getHeight()/2);
		
		record.setSize(this.getWidth()/3, this.getHeight()/15);
		record.setLocation((this.getWidth()-start.getWidth())/2-10, start.getLocation().y + start.getHeight() + 10);
		
		Font font = new Font("", Font.BOLD, 20);
		start.setFont(font);		//각 button의 폰트 설정
		record.setFont(font);
		
		bg.add(start);		//button들을 panel에 추가
		bg.add(record);

		add(bg);			//panel을 frame에 추가
		
		main = this;		//listener에서 this포인터를 사용할 수 있게 변수에 저장
		
		start.addActionListener(new NameListener());		//각 button 별로 listener를 추가
		record.addActionListener(new RecordListener());
	
		
	}
	
	public class NameListener implements ActionListener		//start button을 눌렀을 때의 listener
	{
		public void actionPerformed(ActionEvent e) 
		{
			insert = new JFrame();
			insert.setTitle("Player Name");		//이름 입력을 받는 frame의 인스턴스 생성
			
			JLabel text = new JLabel("\nPlease insert your name\n");	//이름 입력을 원하는 문구
			input = new JTextField(20);
			JButton ok = new JButton("Enter");		//이름 입력을 끝내고 게임을 시작하는 button
			
			insert.setLayout(new FlowLayout(FlowLayout.CENTER, 0, 20));		//frame의 레이아웃을 flow로 설정
			insert.add(text);		//문구, textfield, button를 frame에 추가
			insert.add(input);
			insert.add(ok);
			
			insert.setSize(300, 200);
			insert.setVisible(true);	//화면에 나타냄
			
			ok.addActionListener(new StartGameListener());	//button을 눌렀을 때의 listener 추가
			
		}
	}
	
	public class StartGameListener implements ActionListener	//게임을 시작하는 listener
	{
		public void actionPerformed(ActionEvent e)
		{
			main.setVisible(false);			//mainframe과 이름 입력창을 화면에서 지움
			insert.setVisible(false);
			new PlayGameFrame(input.getText());		//받은 이름을 인자로 넘겨주며 게임 화면을 불러옴
		}
		
	}
	
	public class RecordListener implements ActionListener	//record button을 눌렀을 때의 listener
	{
		public void actionPerformed(ActionEvent e)
		{
			main.setVisible(false);		//mainframe을 화면에서 지우고
			new RecordFrame();			//recordframe을 불러옴
		}
	}

}
