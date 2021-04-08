package 프로젝트_슈팅게임;
import javax.swing.*;

import java.awt.*;

public class MainPanel extends JPanel	//이미지를 붙인 main화면 panel
{
	ImageIcon main_bg = new ImageIcon("image/main.jpg");
	Image img = main_bg.getImage();
	
	public void paintComponent(Graphics g) 
	{
		super.paintComponent(g);
		g.drawImage(img, 0, 0, getWidth(), getHeight(), this);
	}

}
