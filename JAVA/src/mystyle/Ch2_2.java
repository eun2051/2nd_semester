package mystyle;
import java.util.Scanner;

public class Ch2_2 {

	public static void main(String[] args) {
		Scanner a = new Scanner(System.in);
		
		System.out.println("## 택배 보내기입니다. 다음을 각각 입력하세요. ##");
		
		String name;
		System.out.print("받는 사람 : ");
		name = a.nextLine();
		
		String address;
		System.out.print("주소 : ");
		address = a.nextLine();
		
		int weight;
		System.out.print("무게(g) : ");
		weight = a.nextInt();
		
		int result;
		result = 5 * weight;
		
		System.out.println("** 받는 사람 ==> " + name);
		System.out.println("** 주소 ==> " + address);
		System.out.println("** 배송비 ==>" + result + "원");
		
		a.close();
	}
}