package mystyle;
import java.util.Scanner;

// 키, 매력, 나이 입력받기
// 3개의 조건 > 사귄다 / 어장에 넣는다./ 친구로 지낸다./ 무시한다.
public class Ch_5_4 {

	public static void main(String[] args) {
		Scanner s = new Scanner(System.in);
		int height, age;
		String attract;
		
		//사귄다//어장에 넣는다 // 친구로 지낸다 // 무시한다.
		System.out.print("키를 입력하시오 : ");
		height = s.nextInt();
		System.out.print("나이를 입력하시오 : ");
		age = s.nextInt();
		System.out.print("매력을 입력하시오 : ");
		attract = s.next();
		
		if (height >= 170 && age >= 20) {
		    if ((age >= 22 && age <= 25) && (height >= 175 && height <= 190)) {
		        if (attract.equals("강아지상")) {
		            System.out.println("사귄다.");
		        } else {
		            System.out.println("어장에 넣는다...?");
		        }
		    } else {
		        System.out.println("친구로 지낸다.");
		    }
		} else {
		    System.out.println("무시한다.");
		}
		s.close();
	}
			
}