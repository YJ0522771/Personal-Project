package 프로젝트_슈팅게임;
import javax.swing.*;

import java.util.*;
import java.awt.*;
import java.io.*;
import java.nio.file.*;;


public class RecordFrame extends JFrame
{
	private ArrayList<Player> list = new ArrayList<Player>();	//파일 내용을 읽어 저장할 리스트
	private static ObjectInputStream input;
	private static ObjectOutputStream output;
	
	private MainPanel bg;
	private JLabel[][] lists = new JLabel[10][3];	//기록 내용을 보여줄 label리스트
	private JLabel title = new JLabel("Record");
	private JLabel rank = new JLabel("Rank");
	private JLabel name = new JLabel("Name");
	private JLabel score = new JLabel("Score");
	
	
	public RecordFrame()
	{
		setTitle("Shooting Game");
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setSize(4*150, 5*150);
		
		bg = new MainPanel();
		bg.setLayout(new GridLayout(12,3));		//내용을 보기 좋게 배치하기 위해 grid레이아웃 사용
		
		Font font = new Font("", Font.BOLD, 30);
		title.setFont(new Font("", Font.BOLD, 35));		//타이틀 폰트
		
		bg.add(new JLabel(""));		//칸을 맞추기 위한 더미
		bg.add(title);
		bg.add(new JLabel(""));
		
		rank.setFont(font);		//폰트 설정
		name.setFont(font);
		score.setFont(font);
		
		bg.add(rank);			//panel에 추가
		bg.add(name);
		bg.add(score);
		
		readFile();		//파일에서 읽어들임
		
		int i;
		font = new Font("", Font.PLAIN, 25);
		
		for(i=0; i<list.size(); i++)
		{
			Player temp = list.get(i);
			
			
			lists[i] = new JLabel[3];
			
			lists[i][0] = new JLabel("" + (i+1));
			lists[i][1] = new JLabel(temp.getName());
			lists[i][2] = new JLabel("" + temp.getTotal());
			
			lists[i][0].setFont(font);
			lists[i][1].setFont(font);
			lists[i][2].setFont(font);
			
			
			bg.add(lists[i][0]);
			bg.add(lists[i][1]);
			bg.add(lists[i][2]);
		}
		
		for(; i<10; i++)		//grid의 12줄을 다 채우지 못했을 경우 더미 삽입
		{
			bg.add(new JLabel(""));
			bg.add(new JLabel(""));
			bg.add(new JLabel(""));
		}
		
		writeFile();	//다시 파일에 쓴다
		
		add(bg);
		
		
		
		setVisible(true);
		
	}
	
	public void readFile()
	{
		try
		{
			input = new ObjectInputStream(Files.newInputStream(Paths.get("record.ser")));
		}
		catch(IOException ioe)
		{
			try
			{
				output = new ObjectOutputStream(Files.newOutputStream(Paths.get("record.ser")));
				output.close();
			}
			catch(IOException ioe2)
			{
				System.err.println();
			}
			
			try
			{
				input = new ObjectInputStream(Files.newInputStream(Paths.get("record.ser")));
			}
			catch(IOException ioe2)
			{
				System.err.println("Error opening file.");
			}
			
		}
		
		try
		{
			while(true)
			{
				Player temp = (Player) input.readObject();
				
				list.add(temp);
			}
		}
		catch(EOFException eof)
		{
			
		}
		catch(ClassNotFoundException cnf)
		{
			System.err.println("Invaild object type.");
		}
		catch(IOException ioe)
		{
			System.err.println("Error reading from file.");
		}
		
		try
		{
			if(input != null)
				input.close();
		}
		catch(IOException ioe)
		{
			System.err.println("Error closing file.");
		}
	}

	public void writeFile()
	{
		try
		{
			output = new ObjectOutputStream(Files.newOutputStream(Paths.get("record.ser")));
		}
		catch(IOException ioe)
		{
			System.err.println("Error opening file.");
		}
		
		try
		{
			if(list.size() >= 10)
			{
				for(int i=0; i<10; i++)
				{
					output.writeObject(list.get(i));
				}
			}
			else
			{
				for(int i=0; i<list.size(); i++)
				{
					output.writeObject(list.get(i));
				}
			}
		}
		catch(IOException ioe)
		{
			System.err.println();
		}
		
		try
		{
			if(output != null)
				output.close();
		}
		catch(IOException ioe)
		{
			System.err.println("Error closing file.");
		}
	}
	
}
