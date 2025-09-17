package mystyle;
import java.util.Scanner;

//평수를 입력하면 제곱미터로 바꿔주는 프로그램 
public class Ch3_1 {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		
		int place;
		double result;
		System.out.print("평수를 입력하시오 : ");
		place = s.nextInt();
		
		result = place * 3.3;
		
		System.out.print("==> " + result + "제곱미터입니다.");
		
		s.close();
	}
}