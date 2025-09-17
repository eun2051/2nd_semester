package mystyle;
import java.util.Scanner;

public class Ch5_5 {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		int age;
		double score;

		System.out.print("학년을 입력해주세요(1~4) : ");
		age = s.nextInt();
		
		switch(age) {
			case 1:
				System.out.println("교양점수 챙기기");
				break;
			case 2:
				System.out.println("전공 열심히 공부하기");
				break;
			case 3:
				System.out.println("전공 이외의 것도 추가 공부하기");
				break;
			case 4:
				System.out.print("학점을 입력해주세요 : ");
				score = s.nextDouble();
				
				 if (score >= 4.0) {
                     System.out.println("해커톤이나 다른 프로젝트해보기, 인턴해보기");
                 } else if (score >= 3.5) {
                     System.out.println("고학점을 위해 조금만 더 노력하기, 다양한 경험 쌓기");
                 } else if (score >= 3.0) {
                     System.out.println("CS 공부를 조금 더 하기, 프로그램 만드는 능력 키우기");
                 } else {
                     System.out.println("진짜 힘내야지..");
                 }
				break;
			default:
				System.out.println("1~4학년에 해당되지 않습니다.");
		}
	s.close();
	}
}