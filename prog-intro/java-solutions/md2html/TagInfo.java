package md2html;

public class TagInfo implements Comparable<TagInfo>{
    private final String tag;
    private final int position;
    private final int closeInd;

    @Override
    public int compareTo(TagInfo o) {
        return 0;
    }

    public TagInfo(String tag, int position, int closeInd){
        this.tag = tag;
        this.position = position;
        this.closeInd = closeInd;
    }

    public StringBuilder getTag(){
        return new StringBuilder(tag);
    }
    public int getClose(){
        return closeInd;
    }
    public int getPosition(){
        return position;
    }
}
