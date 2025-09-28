import java.util.Objects;
import java.util.Scanner;
import java.util.Random;

public class Matrix implements AutoCloseable
{
    int[][] values;
    Scanner scn = new Scanner(System.in);

    Matrix(int[][] values){
        this.values = values;
    }

    Matrix(int sizeX, int sizeY){
        values = new int[sizeX][sizeY];
        enterValues();
    }

    Matrix(Scanner scn){
        System.out.println("Enter size X");
        int sizeX = scn.nextInt();

        System.out.println("Enter size Y");
        int sizeY = scn.nextInt();

        values = new int[sizeX][sizeY];
        enterValues();
    }

    Matrix(Random rand){
        rand = new Random();
        int sizeX = rand.nextInt(10);
        int sizeY = rand.nextInt(10);

        values = new int[sizeX][sizeY];

        for(int[] row : values ){
            for(int val : row){
                val = rand.nextInt(10);

            }
        }
    }

    Matrix(){
        values = new int[3][3];
    }

    private void enterValues()
    {
        for(int i = 0; i < values.length; i++){
            for(int j = 0; j < values[0].length; j++){
                System.out.println("Enter value " + (i + 1) + ":" + (j + 1));

                values[i][j] = scn.nextInt();
            }
        }
    }

    public String toString(){
        String output = "";

        for (int[] row : values){
            for (int value : row){
                output += value + " ";
            }
            output += '\n';
        }
        return output;
    }

    public void findMaxElement(){
        int max = values[0][0];

        for(int[] row : values){
            for(int val : row){
                if(val > max){
                    max = val;
                }
            }
        }

        System.out.println("Max value : " + max);
    }

    public void findMinElement(){
        int min = values[0][0];

        for(int[] row : values){
            for(int val : row){
                if(val < min){
                    min = val;
                }
            }
        }

        System.out.println("Min value : " + min);
    }

    public void close() throws Exception {
        scn.close();
    }

}
