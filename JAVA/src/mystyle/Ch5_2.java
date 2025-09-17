package mystyle;
import java.util.Scanner;

public class Ch5_2 {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		int money;
		//String menu;
		System.out.print("예산을 입력하시오: ");
		money = s.nextInt();
		if (money > 5000 && money <= 20000) System.out.println("학생식당");
		if (money > 20000 && money <= 50000) System.out.println("치킨");
		if (money > 50000 && money <= 200000) System.out.println("육회");
		if (money > 200000) System.out.println("인터불고 호텔");
		s.close();
	}
}