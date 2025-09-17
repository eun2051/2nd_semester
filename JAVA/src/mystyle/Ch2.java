package mystyle;
import java.util.Scanner;

public class Ch2 {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		
		int a;
		int b;
		int add, ab, sb;
		
		a = s.nextInt();
		b = s.nextInt();
		
		add = a + b;
		ab = a - b;
		sb = a * b;
		
		System.out.println("a + b ==> " + add );
		System.out.println("a - b ==> " + ab );
		System.out.println("a * b ==> " + sb );
		
		s.close();
		
	}
}