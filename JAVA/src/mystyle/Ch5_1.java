package mystyle;
import java.util.Scanner;

public class Ch5_1 {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		int age;
		System.out.print("나이를 입력하시오: ");
		age = s.nextInt();
		if (age < 18 ) System.out.println("입장가능");
		s.close();
	}
}