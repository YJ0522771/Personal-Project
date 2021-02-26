package 프로젝트_슈팅게임;

import java.awt.Graphics;
import java.awt.Image;

import javax.swing.ImageIcon;
import javax.swing.JPanel;

public class PlayPanel extends JPanel		//배경 이미지를 붙이기 위한 플레이 panel
{
	
	ImageIcon main_bg = new ImageIcon("image/play.jpg");
	Image img = main_bg.getImage();
		
	public void paintComponent(Graphics g) 
	{
		super.paintComponent(g);
		g.drawImage(img, 0, 0, getWidth(), getHeight(), this);
	}

}
