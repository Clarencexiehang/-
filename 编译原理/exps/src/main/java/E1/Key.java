package E1;


import lombok.Data;

@Data
public class Key {
    String str;  //单词
    String memo;//助记符
    Object value; //值

    public Key(String str, String remStr, Object value) {
        this.str = str;
        this.memo = remStr;
        this.value = value;
    }
}
