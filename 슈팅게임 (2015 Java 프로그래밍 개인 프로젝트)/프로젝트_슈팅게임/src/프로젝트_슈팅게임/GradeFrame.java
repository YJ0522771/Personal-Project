package 프로젝트_슈팅게임;
import javax.swing.*;

import java.awt.*;

public class GradeFrame extends JFrame		//최종 스코어에 따른 등급을 보여주는 화면
{
	private MainPanel bg;
	private JLabel title = new JLabel("Your grade is");		//grade와 함께 내보낼 문구
	private JLabel grade;				//grade를 표시할 label
	private JLabel comment;
	
	public GradeFrame(char res)		//PlayGameFrame에서 플레이어의 최종 등급을 넘겨받는다
	{
		setTitle("Shooting Game");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		setSize(4*150, 5*150);
		
		bg = new MainPanel();		//배경화면 이미지가 설정된 panel
		bg.setLayout(new FlowLayout(FlowLayout.CENTER, 30, 150));	//panel의 레이아웃을 flow로 설정, 가로 세로의 gap을 각각 30 150으로 설정
		
		title.setFont(new Font("", Font.PLAIN, 60));		//title의 폰트 설정
		
		grade = new JLabel("" + res);
		grade.setFont(new Font("", Font.BOLD, 80));			//grade의 폰트 설정
		
		bg.add(title);		//title과 grade를 panel에 붙임
		bg.add(grade);
		
		comment = new JLabel();
		
		switch(res)			//grade에 따라 각각 다른 멘트를 함께 넣는다
		{
			case 'A' :
				comment.setText("Great!!");
				break;
			case 'B' :
				comment.setText("Good!");
				break;
			case 'C' :
				comment.setText("So-So");
				break;
			case 'D' :
				comment.setText("Poor!");
				break;
			case 'F' :
				comment.setText("Terrible!!");
				break;
		}
		
		comment.setFont(new Font("", Font.PLAIN, 60));		//펜트를 panel에 붙임
		bg.add(comment);
		
		add(bg);			//panel을 frame에 붙임
		
		setVisible(true);	//화면을 보여줌
	}
}
