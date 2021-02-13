import java.io.BufferedReader;
import java.io.FileReader;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.InputStreamReader;
import java.util.*;

class DateRange {
  public String startDate;
  public String endDate;

  public DateRange(String startDate, String endDate) {
    this.startDate = startDate;
    this.endDate = endDate;
  }
}

class Phone {
  public String phone;
  public Hashtable<String, Integer> startDates;
  public Hashtable<String, Integer> endDates;

  public Phone(String phone, DateRange d) {
    this.phone = phone;
    this.startDates = new Hashtable<String, Integer>();
    this.endDates = new Hashtable<String, Integer>();
    this.startDates.put(d.startDate, 1);
    this.endDates.put(d.endDate, 1);
  }

  public void insertDateInto(DateRange d) {
    if (startDates.containsKey(d.endDate)) {
      startDates.remove(d.endDate);
    } else {
      endDates.put(d.endDate, 1);
    }
    if (endDates.containsKey(d.startDate)) {
      endDates.remove(d.startDate);
    } else {
      startDates.put(d.startDate, 1);
    }
  }
  public String getStartDateOfCurrentUser() {
    List<String> dates = Collections.list(startDates.keys());
    Collections.sort(dates);
    String startDate = dates.get(dates.size()-1);
    return String.format("%s,%s", phone, startDate);
  }
}


class Solution {
  public static void main(String[] args) throws Exception {
    BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
    Hashtable<String, Phone> rs = new Hashtable<String, Phone>();
    br.readLine();
    String row = "";
    while ((row = br.readLine()) != null) {
      String[] arr = row.split(",");
      String phone = arr[0];
      String startDate = arr[1];
      String endDate = (arr.length == 3) ? arr[2] : "";
      if (!rs.containsKey(phone)) {
        rs.put(phone, new Phone(phone, new DateRange(startDate, endDate)));
      } else {
        Phone t = rs.get(phone);
        t.insertDateInto(new DateRange(startDate, endDate));
        rs.put(phone, t);
      }
    }

    ArrayList<String> lines = new ArrayList<String>();
    Enumeration<String> e = rs.keys();
    while (e.hasMoreElements()) {
      String phone = e.nextElement();
      Phone t = rs.get(phone);
      lines.add(t.getStartDateOfCurrentUser()); 
    }
    String out = String.join("\n", lines.toArray(new String[lines.size()]));
    System.out.println(out);
    // write to file
    String csvFile = "output.csv";
    BufferedWriter bw = new BufferedWriter(new FileWriter(csvFile));
    bw.write("PHONE_NUMBER,REAL_ACTIVATION_DATE\n");
    bw.write(out);
    bw.close();
  }
}