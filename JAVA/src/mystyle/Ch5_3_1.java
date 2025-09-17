package mystyle;
import java.util.Scanner;

public class Ch5_3_1 {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		int money;
		
		System.out.print("예산을 입력하시오: ");
		money = s.nextInt();
		
		if (money > 200000)
			System.out.println("인터불고 호텔");
		else
			if (money > 50000)
				System.out.println("육회");
			else
				if (money > 20000)
					System.out.println("치킨");
				else
					if (money > 5000)
						System.out.println("학생식당");
					else
						System.out.println("굶기");
		s.close();
	}
}