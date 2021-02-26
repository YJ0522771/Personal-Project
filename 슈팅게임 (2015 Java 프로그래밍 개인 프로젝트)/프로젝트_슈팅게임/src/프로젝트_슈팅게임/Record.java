package 프로젝트_슈팅게임;
import java.util.*;
import java.io.*;
import java.nio.file.*;;

public class Record 	//기록을 파일에 출력
{
	private ArrayList<Player> list = new ArrayList<Player>();	//파일에 내용을 잠시 저장시켜둘 리스트
	private static ObjectInputStream input;
	private static ObjectOutputStream output;
	
	public Record(Player user)
	{
		try
		{
			input = new ObjectInputStream(Files.newInputStream(Paths.get("record.ser")));	//읽기모드로 파일을 연다
		}
		catch(IOException ioe)
		{
			try		//파일이 아직 존재하지 않으면
			{
				output = new ObjectOutputStream(Files.newOutputStream(Paths.get("record.ser")));	//쓰기모드를 통해 파일 생성
				output.close();
			}
			catch(IOException ioe2)
			{
				System.err.println();
			}
			
			try
			{
				input = new ObjectInputStream(Files.newInputStream(Paths.get("record.ser")));		//다시 읽기 모드로 연다
			}
			catch(IOException ioe2)		//그래도 안 되면 에러 문구 출력
			{
				System.err.println("Error opening file.");
			}
			
		}
		
		
		try
		{
			while(true)		//eof예외를 통해 파일 끝까지 읽어 리스트에 저장
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
			if(input != null)		//읽기 용으로 연 파일을 닫음
				input.close();
		}
		catch(IOException ioe)
		{
			System.err.println("Error closing file.");
		}
		
		try
		{
			output = new ObjectOutputStream(Files.newOutputStream(Paths.get("record.ser")));	//쓰기 모드로 파일을 연다
		}
		catch(IOException ioe)
		{
			System.err.println("Error opening file.");
		}
		
		int i;
		
		for(i=0; list.size()!=0 && i<list.size(); i++)	//파일에서 막 읽어들인 리스트는 이미 sorting이 된 상태이므로
		{
			if(user.getTotal() > list.get(i).getTotal())	//새로 플레이한 정보의 적절한 위치를 찾아
			{
				break;
			}
		}
		
		list.add(i, user);		//해당 위치에 삽입
		
		try
		{
			if(list.size() >= 10)	//리스트 중 최대 10개만 파일에 쓴다
			{
				for(i=0; i<10; i++)
				{
					output.writeObject(list.get(i));
				}
			}
			else
			{
				for(i=0; i<list.size(); i++)
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
			if(output != null)		//파일을 닫음
				output.close();
		}
		catch(IOException ioe)
		{
			System.err.println("Error closing file.");
		}
	}

}
