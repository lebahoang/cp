import java.util.ArrayList;
// javac -cp ".;*" jv.java  && java -Xmx512M -Xss64M -DONLINE_JUDGE=true -Duser.language=en -Duser.region=US -Duser.variant=US Main
interface OrderPaymentInterface {
    public int getPaidMoney(Order order);
}
abstract class PromotionAbstract implements OrderPaymentInterface {
    private OrderPayment orderPayment;
    public PromotionAbstract(OrderPayment orderPayment) {
        this.orderPayment = orderPayment;
    }
    public int getPaidMoney(Order order) {
        return this.orderPayment.getPaidMoney(order);
    }
}
class Item {
    private int price;
    public Item(int price) {
        this.price = price;
    }
    public int getPaidMoney(int amount) {
        return amount * price;
    }
}
class Order {
    private Item[] items;
    public Order(Item[] items) {
        this.items = items;
    }
    public Item[] getItems() {
        return this.items;
    }
}
class OrderPayment implements OrderPaymentInterface {
    public int getPaidMoney(Order order) {
        int total = 0;
        for (Item x : order.getItems()) {
            total += x.getPaidMoney(10);
        }
        return total;
    }
}

class PromotionByAmountOfItem extends PromotionAbstract {
    public PromotionByAmountOfItem(OrderPayment orderPayment) {
        super(orderPayment);
    }
    public int getPaidMoney(Order order) {
        int total = super.getPaidMoney(order);
        return total - this.getDisCount(order);
    }
    private int getDisCount(Order order) {
        return 100;
    }
}

class Main {
    public void run() {
        Item[] i = {new Item(100)};
        Order order = new Order(i);
        OrderPayment payment = new OrderPayment();
        PromotionByAmountOfItem p = new PromotionByAmountOfItem(payment);
        System.out.println(p.getPaidMoney(order));
    }
    public static void main(String[] args) {
        Main m = new Main();
        m.run();
    }
}