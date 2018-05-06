import java.util.ArrayList;
import java.util.Scanner;
import java.io.*;
import java.text.DecimalFormat;

public class pagerank {
    static ArrayList<link> linkek = new ArrayList<link>();

    public static void main(String[] args){

	double d;

	beolvasas();						
	
	Scanner scan = new Scanner(System.in);
	
	System.out.print("Add meg a 'd' erteket: ");
	d = scan.nextDouble();

	for(int i = 0; i < linkek.size(); i++){			
	    System.out.print(linkek.get(i).nev + " : ");
	    for(int j = 0; j < linkek.get(i).mutat.size(); j++){
		System.out.print(linkek.get(i).mutat.get(j) + ", ");
	    }
	    System.out.println();	
	}
	double[][] link_matrix = new double[linkek.size()][linkek.size()];
	double[] PR = new double[linkek.size()];
	double[] PRs = new double[linkek.size()];

	DecimalFormat ket_tizedes = new DecimalFormat("#.##");	

	for(int i = 0; i < linkek.size(); i++){
	    PR[i] = 0;
	    PRs[i] = 1.0 / linkek.size();
	    for(int j = 0; j < linkek.size(); j++){
		boolean benne_van = false;
		for(int k = 0; k < linkek.get(j).mutat.size(); k++){
		    if(linkek.get(j).mutat.get(k).equals(linkek.get(i).nev)){
			benne_van = true;
			link_matrix[i][j] = 1.0 / linkek.get(j).mutat.size();
			break;
		    }
		}
		if(!benne_van){
		    link_matrix[i][j] = 0.0;
		}
		System.out.print(ket_tizedes.format(link_matrix[i][j]) + "\t");
	    }
	    System.out.println();
	}

	while(true){

	    for(int i = 0; i < linkek.size(); i++){
		double temp = 0;
		for(int j = 0; j < linkek.size(); j++){
		    temp += link_matrix[i][j]*PRs[j];
		}
		PR[i] = (1-d)/linkek.size()+d*temp;
	    }
	    if(tavolsag(PR, PRs) < 0.0000000001){
		break;
	    }
	    for(int i = 0; i < linkek.size(); i++){
		PRs[i] = PR[i];
	    }
	}
	for(int i = 0; i < linkek.size(); i++){
	    System.out.println((i+1) + ".: " + PR[i]);
	}

    }

    static void beolvasas(){
	BufferedReader br = null;
	try {
    	    File file = new File("adatok.txt");
            br = new BufferedReader(new FileReader(file));

    	    String temp;
   	    while ((temp = br.readLine()) != null) {
		linkek.add(new link(temp));
		while((temp = br.readLine()) != null && temp.length() != 0){
		    linkek.get(linkek.size()-1).mutat.add(temp);
		}
            }
	    br.close();
	} catch (IOException e) {
	    System.err.println("Nem található a fájl ...");
	}
    }
    static double tavolsag(double[] PR, double[] PRs){
	double osszeg = 0;

	for(int i = 0; i < linkek.size(); i++){
	    osszeg += Math.abs(PR[i]-PRs[i]);
	}
	return osszeg;
    }
}