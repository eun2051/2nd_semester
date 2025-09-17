package mystyle;
import java.util.Scanner;

public class Ch2_1 {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		
		int num;
		System.out.println("학번을 입력하시오.");
		num = s.nextInt();
		
		String name;
		System.out.println("이름을 입력하시오.");
		name = s.next();
		
		String answer;
		System.out.println("할 말을 입력하시오.");
		answer= s.next();
		
		System.out.println("학번 : " + num);
		System.out.println("이름 : " + name );
		System.out.println("총장에게 하고싶은 말 : " + answer );
		
		s.close();
	}
}