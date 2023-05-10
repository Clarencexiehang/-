package E1;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

public class Lexer {
    //单词
    static String key_list[] = {"break", "char", "do", "double", "else", "if",
            "int", "return", "void", "while",
            "+", "-", "*", "/",
            ">", "<", "=",
            "{", "}", "(", ")", ",", ";"
    };
    //助记符
    static String memo_list[] = {
            "BREAK", "CHAR", "DO", "DOUBLE", "ELSE", "IF",
            "INT", "RETURN", "VOID", "WHILE",
            "ADD", "SUB", "MUL", "DIV",
            "GT", "LT", "ASSIGN",
            "LB", "RB", "LR", "RR", "COMMA", "SEMI"
    };
    //单词边界符号
    static char[] boundChar = {' ', '\r', '\n', '<', '>', '=', '+', '-', '*', '/', '(', ')', '{', '}', '[', ']', ';',',','!'};

    static ArrayList<Token> tokens = new ArrayList<>();    //符号表
    static String file_str;                                //所编译文件内容
    static char currentChar = '\0';                        //读取的字符值
    static int pos;                                        //编译时读取字符的位置

    /**
     * 构造函数，读取指定文件的内容转换为字符串
     * @throws IOException
     */
    public Lexer() throws IOException {
        try {
            //读取源代码串
            FileReader fileReader = new FileReader("files/source.c");
            char[] code = new char[1024];
            fileReader.read(code);
            file_str = new String(code);    //代码串
        } catch (IOException e) {
            System.out.println("IO Exception");
        }

    }

    /**
     * 判断扫描字符是否是边界符
     * @param currentChar 所扫描的字符
     * @return
     */
    public static boolean isBoundChar(char currentChar) {
        boolean flag = false;
        for (char ch : boundChar) {
            if (ch == currentChar) {
                flag = true;
                break;
            }
        }
        return flag;
    }

    /**
     * 存储边界符到tokens中，其中>= <= != ==单独处理
     * @param ch
     */
    public static void StoreBoundChar(char ch) {
        if (ch == '>' && file_str.charAt(pos + 1) == '=') {
            pos++;
            Token token = new Token("GE", "_");
            tokens.add(token);
        } else if (ch == '<' && file_str.charAt(pos + 1) == '=') {
            pos++;
            Token token = new Token("LE", "_");
            tokens.add(token);
        } else if (ch == '=' && file_str.charAt(pos + 1) == '=') {
            pos++;
            Token token = new Token("EQ", "_");
            tokens.add(token);
        } else if (ch == '!' && file_str.charAt(pos + 1) == '=') {
            pos++;
            Token token = new Token("NE", "_");
            tokens.add(token);
        } else {
            if (ch == ' ' || ch == '\r' || ch == '\n') {
                return;
            }
            //查找助记符
            for (int k = 0; k < key_list.length; k++) {
                if (String.valueOf(ch).equals(key_list[k])) {
                    Token token = new Token(memo_list[k], "_");
                    tokens.add(token);
                    break;
                }
            }
        }
    }

    /**
     * 判断字符串是否是关键字
     * @param s 字符串
     * @return
     */
    public static boolean isKeyWord(String s) {
        boolean flag = false;
        for (int k = 0; k < key_list.length; k++) {
            //如果匹配到关键词，存入token
            if (s.equals(key_list[k])) {
                flag = true;

                Token token = new Token(memo_list[k], "_");
                tokens.add(token);
                break;
            }
        }
        return flag;
    }

    /**
     * 判断字符是否是数字【0-9】
     * @param ch
     * @return
     */
    public static boolean isDigit(char ch) {
        boolean flag = false;
        if (ch >= '0' && ch <= '9') {
            flag = true;
        }
        return flag;
    }

    /**
     * 词法分析
     * 1.数字常量的识别
     * 2.边界符的识别
     * 3.字符串的识别
     * 4.关键字的识别
     * 5.注释的识别
     * @throws Exception
     */
    static void Lexical_Analysis() throws Exception {
        for (pos = 0; pos < file_str.length(); pos++) {
            currentChar = file_str.charAt(pos);

            //如果为注释
            if (currentChar == '/' && file_str.charAt(pos + 1) == '*') {
                pos += 2;
                while (pos < file_str.length()) {
                    if (file_str.charAt(pos) == '*' && file_str.charAt(pos + 1) == '/') {
                        pos = pos + 2;
                        break;
                    }
                    pos++;
                }
            }

            //如果为边界符
            else if (isBoundChar(currentChar)) {//System.out.println(pos+" "+file_str.charAt(pos));
                StoreBoundChar(currentChar);
                continue;
            }

            //如果为关键字
            else if ((currentChar >= 'a' && currentChar <= 'z') || (currentChar >= 'A' && currentChar <= 'Z')) {
                StringBuilder strUnit = new StringBuilder();     //单词单元拼接

                while (pos < file_str.length()) {
                    currentChar = file_str.charAt(pos);

                    //如果是分界符，判断是关键字还是标识符
                    if (isBoundChar(currentChar)) {
                        if (!isKeyWord(strUnit.toString())) {
                            strUnit.insert(0,"\"");
                            strUnit.append("\"");
                            Token token = new Token("ID", strUnit.toString());
                            tokens.add(token);
                        }

                        StoreBoundChar(currentChar);
                        break;
                    }
                    //如果不是分界符,连接字符
                    else {
                        strUnit.append(currentChar);
                        pos++;
                    }
                }
            }

            //如果是字符常量
            else if (currentChar == '\"' || currentChar=='L') {
                StringBuilder strUnit = new StringBuilder();     //单词单元拼接
                strUnit.append(currentChar);
                pos++;

                while (pos < file_str.length()) {
                    currentChar = file_str.charAt(pos);
                    //如果是 " 存入tokens
                    if (currentChar == '\"') {
                        //检查字符串格式是否符合规范
                        if (!isBoundChar(file_str.charAt(pos + 1))) {
                            throw new Exception("字符串格式错误，请检查！");
                        }
                        strUnit.append(currentChar);
                        Token token = new Token("STRING", strUnit.toString());
                        tokens.add(token);
                        break;
                    } else {
                        strUnit.append(currentChar);
                        pos++;
                    }
                }
            }

            //如果是常数
            else if (isDigit(currentChar)) {
                StringBuilder numUnit = new StringBuilder();     //单词单元拼接
                numUnit.append(currentChar);

                boolean toTheOutermostLayer = false;    //是否要跳转到最外层
                while (pos < file_str.length()) {

                    if(toTheOutermostLayer) break;

                    char nextChar = file_str.charAt(pos + 1);

                    //如果开头为0，那么需要考虑0x3F 0Xa2U 0x12u这种情况
                    if (currentChar == '0' && (nextChar == 'x' || nextChar == 'X')) {
                        numUnit.append(nextChar);
                        pos+=2;

                        while (pos < file_str.length()) {
                            currentChar = file_str.charAt(pos);
                            if (isDigit(currentChar)||(currentChar>='a'&&currentChar<='f')||(currentChar>='A'&&currentChar<='F')) {
                                numUnit.append(currentChar);
                            }
                            //如果检测到U|u|L|l,结束，放入tokens
                            else if (currentChar == 'u' || currentChar == 'U' || currentChar == 'L' || currentChar == 'l') {
                                numUnit.append(currentChar);
                                Token token = new Token("NUM", numUnit.toString());
                                tokens.add(token);
                                toTheOutermostLayer = true;
                                break;
                            }
                            //如果检测到边界，存入tokens
                            else if (isBoundChar(currentChar)) {
                                Token token = new Token("NUM", numUnit.toString());
                                tokens.add(token);
                                StoreBoundChar(currentChar);
                                toTheOutermostLayer = true;
                                break;
                            }
                            //否则报错，该常数不符合规范
                            else {
                                throw new Exception("16进制的常数格式错误，请检查！");
                            }
                            pos++;
                        }
                    }


                    //如果不是16进制0x，那么有 12.34E+56 F|f|L|l 或者123U|u|L|l 形式
                    else {
                        pos++;
                        while (pos < file_str.length()) {
                            if(toTheOutermostLayer) break;

                            currentChar = file_str.charAt(pos);

                            if ((currentChar >= '0' && currentChar <= '9') || currentChar == '.') {
                                numUnit.append(currentChar);
                            }

                            //判断指数形式是否正确
                            else if (currentChar == 'E' || currentChar == 'e') {
                                numUnit.append(currentChar);
                                //如果E后面是+|-，合法，但是只能出现一次
                                nextChar = file_str.charAt(pos + 1);
                                if (nextChar == '+' || nextChar == '-') {
                                    numUnit.append(nextChar);
                                    pos++;
                                }
                                //E+- 后面是否合法
                                while (pos < file_str.length()) {
                                    pos++;
                                    currentChar = file_str.charAt(pos);
                                    if (currentChar == 'f' || currentChar == 'F' || currentChar == 'l' || currentChar == 'L') {
                                        numUnit.append(currentChar);
                                        Token token = new Token("NUM", numUnit.toString());
                                        tokens.add(token);
                                        toTheOutermostLayer = true;
                                        //这里pos-1是因为这里本来应该跳到第一层循环，但是用的标志量实现，外层的while的pos多加了一次1，提前减掉
                                        pos--;
                                        break;
                                    } else if (isDigit(currentChar)) {
                                        numUnit.append(currentChar);
                                    } else if (isBoundChar(currentChar)) {
                                        Token token = new Token("NUM", numUnit.toString());
                                        tokens.add(token);
                                        StoreBoundChar(currentChar);
                                        toTheOutermostLayer = true;
                                        break;
                                    } else {
                                        throw new Exception("指数形式的常数格式错误，请检查！");
                                    }
                                }


                            } else if (isBoundChar(currentChar)) {
                                Token token = new Token("NUM", numUnit.toString());
                                tokens.add(token);
                                StoreBoundChar(currentChar);
                                toTheOutermostLayer = true;
                                break;
                            } else {
                                throw new Exception("非16进制的常数格式错误，请检查！");
                            }
                            pos++;
                        }
                    }
                }
            }
        }
    }

    public static void main(String[] args) throws Exception {
        Lexer lexer = new Lexer();
        Lexical_Analysis();

        for (Token token : tokens) {
            System.out.println("(" + token.getName() + "," + token.getValue() + ")");
        }
    }
}