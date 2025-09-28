import java.util.*;

public class AnagramFinder {

    public static void findAnagrams(String sentence)
    {
        System.out.println("Sentence : " + sentence);

        sentence = sentence.replaceAll("[^a-zA-Zа-яА-Я]", " ").trim();

        List<String> words = new ArrayList<>();
        ArrayList<String> anagrams = new ArrayList<>();

        Collections.addAll(words, sentence.split("\\s+"));

        if (words.isEmpty())
        {
            System.out.println("Sentence contains no words");
            return;
        }

        String firstWord = sortLetters(words.getFirst());
        words.remove(0);

        System.out.println("Anagrams :");
        for (String word : words)
        {
            String sortedWord = sortLetters(word);
            if(sortedWord.toLowerCase().equals(firstWord.toLowerCase()))
            {
                System.out.println(word);
            }
        }
    }

    private static String sortLetters(String word) {
        char[] characters = word.toCharArray();
        Arrays.sort(characters);
        return new String(characters);
    }
}
