
import java.io.*;


public class MyScaner {
    public Reader reader;
    public int beginR;
    public int endR;
    public char[] readerCh;
    public final int SIZE = (int)Math.pow(2, 20);
    public int beginStr;
    public int endStr;
    public int resInt;
    public String word;
    public boolean isNextLine;

    public MyScaner(InputStream in) throws IOException {
        this.reader = new InputStreamReader(in, "utf8");
        this.readerCh = new char[SIZE];
        this.isNextLine = false;
        readerBuffer();
    }
    public MyScaner(String inputFile, String set) throws UnsupportedEncodingException, FileNotFoundException, IOException {
        this.reader = new InputStreamReader(new FileInputStream(inputFile), set);
        this.readerCh = new char[SIZE];
        readerBuffer();
    }
    public MyScaner(String str) throws IOException {
        this.reader = new StringReader(str);
        this.readerCh = new char[SIZE];
        readerBuffer();
    }
    
    public void readerBuffer() throws IOException {
        this.beginR = 0;
        this.endR = reader.read(readerCh);
    }

    public void close() throws IOException {
        reader.close();
    }

    public boolean HasNextHexSymbol(int intr) {
        return('0' <= intr && intr <= '9') 
        || ('a' <= intr && intr <= 'f')
        || '-' == intr;
    }
    public boolean HasNextIntSymbol(int intr) {
        
        return('0' <= intr && intr <= '9') 
        || intr == '-';
    }

    public int hex2decimal(String s) {
        int val;
        if (s.charAt(0) == '-') {
            val = -Integer.parseUnsignedInt(s.substring(1), 16);
        } else {
            val = Integer.parseUnsignedInt(s, 16);
        }
        return val;
    }
    public boolean isNextALetter(char ch) {
        return (Character.getType(ch) == Character.DASH_PUNCTUATION || Character.isLetter(ch) || ch == '\'');
    }
    
    public boolean isSeparator(char ch){
        return System.lineSeparator().contains(Character.toString(ch));
    }
    public boolean isSeparator(String str){
        return System.lineSeparator().contains(str);
    }
    public String nextLine() throws IOException{
        StringBuilder sb = new StringBuilder();
        int now = beginR;
        if (now >= endR) {
            readerBuffer();
            now = 0;
        }
        while (endR != -1) {
            if (isSeparator(readerCh[now])) {
                StringBuilder linesep = new StringBuilder(Character.toString(readerCh[now]));
                now++;
                if (now >= endR) {
                    readerBuffer();
                    now = 0;
                }
                if (isSeparator(readerCh[now])) {
                    linesep.append(readerCh[now]);
                    while (isSeparator(linesep.toString()) && endR != -1) {
                        now++;
                        if (now >= endR) {
                            readerBuffer();
                            now = 0;
                        }
                        linesep.append(readerCh[now]);
                    }
                    now--;
                } else {
                    now--;
                }
                break;
            }
            sb.append(readerCh[now]);
            now++;
            if (now >= endR) {
                readerBuffer();
                now = 0;
            }
        }
        beginR = now + 1;
        if (beginR >= endR) {
            readerBuffer();
            now = 0;
        }
        return sb.toString();
    }
    public boolean hasNextLine() throws IOException{
        return endR != -1;
    }
    public boolean hasNextHex() throws IOException{
        StringBuilder sb = new StringBuilder();
        int now = beginR;
        while (endR != -1) {
            if (!HasNextHexSymbol(readerCh[now]) && sb.length() == 0) {
                now++;
            } else {
                if (HasNextHexSymbol(readerCh[now])) {
                    sb.append(readerCh[now]);
                    now++;
                } else {
                    break;
                }
            }
            if (now == endR) {
                readerBuffer();
                now = 0;
            }
        }
        beginR = now + 1;
        if (beginR >= endR) {
            readerBuffer();
            now = 0;
        }
        if (sb.length() == 0) {
            return false;
        }
        this.resInt = hex2decimal(sb.toString());
        return true;
    }
    public boolean hasNextHexFast() throws IOException{
        StringBuilder sb = new StringBuilder();
        StringBuilder sep = new StringBuilder();
        while (endR != -1) {
            if (beginR >= endR) {
                readerBuffer();
            }
            if (HasNextHexSymbol(readerCh[beginR])) {
                sb.append(readerCh[beginR]);
            } else {
                if (sb.length() != 0) {
                    this.resInt = hex2decimal(sb.toString());
                    return true;
                } else {
                    if (isSeparator(readerCh[beginR])) {
                        sep.append(readerCh[beginR]);
                        while (isSeparator(sep.toString())) {
                            beginR++;

                            if (beginR >= endR) {
                                readerBuffer();
                            }
                            sep.append(readerCh[beginR]);
                        }
                        return false;
                    }
                }
            }
            beginR++;
        }
        return false;
    }
    public int nextHex() {
        return this.resInt;
    }

    public boolean hasNextInt() throws IOException{
        StringBuilder sb = new StringBuilder();
        int now = beginR;
        while (endR != -1) {
            if (!HasNextIntSymbol(readerCh[now]) && sb.length() == 0) {
                now++;
            } else {
                if (HasNextIntSymbol(readerCh[now])) {
                    sb.append(readerCh[now]);
                    now++;
                } else {
                    break;
                }
            }
            if (now == endR) {
                readerBuffer();
                now = 0;
            }
        }
        beginR = now + 1;
        if (beginR >= endR) {
            readerBuffer();
            now = 0;
        }
        if (sb.length() == 0) {
            return false;
        }
        this.resInt = Integer.parseInt(sb.toString());
        return true;
    }
    public int nextInt() throws IOException {
        return this.resInt;
    }

    public  boolean hasNextIntFast() throws IOException {
        StringBuilder sb = new StringBuilder();
        StringBuilder sep = new StringBuilder();
        while (endR != -1) {
            if (beginR >= endR) {
                readerBuffer();
            }
            if (HasNextIntSymbol(readerCh[beginR])) {
                sb.append(readerCh[beginR]);
            } else {
                if (sb.length() != 0) {
                    this.resInt = Integer.parseInt(sb.toString());
                    return true;
                } else {
                    if (isSeparator(readerCh[beginR])) {
                        sep.append(readerCh[beginR]);
                        while (isSeparator(sep.toString())) {
                            beginR++;

                            if (beginR >= endR) {
                                readerBuffer();
                            }
                            sep.append(readerCh[beginR]);
                        }
                        return false;
                    }
                }
            }
            beginR++;
        }
        return false;
    }


    public boolean hasNextWord() throws IOException {
        StringBuilder sb = new StringBuilder();
        int now = beginR;
        while (endR != -1) {
            if (!isNextALetter(readerCh[now]) && sb.length() == 0) {
                now++;
            } else {
                if (isNextALetter(readerCh[now])) {
                    sb.append(readerCh[now]);
                    now++;
                } else {
                    break;
                }
            }
            if (now == endR) {
                readerBuffer();
                now = 0;
            }
        }
        beginR = now + 1;
        if (beginR >= endR) {
            readerBuffer();
            now = 0;
        }
        if (sb.length() == 0) {
            return false;
        }
        this.word = sb.toString();
        return true;
    }
    public String nextWord() {
        return this.word;
    }
    public boolean isNextLine() {
        if (this.isNextLine) {
            this.isNextLine = false;
            return !this.isNextLine;
        }
        return this.isNextLine;
    }
}
