import java.io.*;

public class CRLEEncoder implements RLEInterface{
	
	private final String inputFilename;
    private final String outputFilename;

	public CRLEEncoder(String txt1, String txt2) {
		inputFilename = txt1;
		outputFilename = txt2;
	}
	
	public void encodeFile() throws Exception {
		if (inputFilename.isEmpty())
			throw new Exception("\nFile is Empty!");

		BufferedInputStream in = new BufferedInputStream(new FileInputStream(inputFilename));
		BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(outputFilename));;

        long fileLen = in.available();
        if (fileLen == 0) throw new Exception("\nFile is Empty!");

        System.out.println("Original Size : " + fileLen + "\n");


        int count = 1, currentCh = 0, prevCh = 0;
        out.write(rleSignature.getBytes());

        prevCh = in.read();
        for (long i = 1; i < fileLen;) {
			do {
				currentCh = in.read();
				i++;
				if (prevCh == currentCh) count++;
				if (count >= 255) break;
			} while (prevCh == currentCh && i < fileLen);

            if (count >= toleranceFrequency || prevCh == ESCAPECHAR){
                out.write(ESCAPECHAR);
                out.write((char)prevCh);
                out.write((char)count);
            } else {
                for (int k = 0; k < count; ++k)
                    out.write(prevCh);
            }

            if (prevCh == currentCh) count = 0; else count = 1;
            prevCh = currentCh;
        }
        out.close();

        long outputFileLen = new File(outputFilename).length();
        float compress_ratio = (float)(outputFileLen*100) / (float)fileLen;
        System.out.println("Compressed File Size : " + outputFileLen + "\n");
        System.out.println("Compressed Ratio : " + compress_ratio + "% \n");
	}
//
//    public void encodeFileRGB() throws Exception {
//        if (inputFilename.isEmpty())
//            throw new Exception("\nFile is Empty!");
//
//        BufferedInputStream in = new BufferedInputStream(new FileInputStream(inputFilename));
//        BufferedOutputStream out = new BufferedOutputStream(new FileOutputStream(outputFilename));;
//
//        long fileLen = in.available();
//        if (fileLen == 0) throw new Exception("\nFile is Empty!");
//
//        System.out.println("Original Size : " + fileLen + "\n");
//        // skip useless
//        for (int i = 0; i < 54; ++i)
//            in.read();
//
//        int count = 1, r = 0, g = 0, b = 0, prevCh = 0;
//        out.write(rleSignature.getBytes());
//        System.out.println(fileLen + " " + (fileLen - 54) % 3);
//        int prev_r = in.read(), prev_g = in.read(), prev_b = in.read();
//        for (long i = 1; i < fileLen;) {
//            boolean isEqual = false;
//            do {
//                r = in.read(); g = in.read(); b = in.read();
//                i++;
//                isEqual = prev_r == r && prev_g == g && prev_b == b;
//                if (isEqual) count++;
//                if (count >= 255) break;
//            } while (isEqual && i < fileLen);
//
//            if (count >= toleranceFrequency || r == ESCAPECHAR || g == ESCAPECHAR || b == ESCAPECHAR){
//                out.write(ESCAPECHAR);
//                out.write((char)prevCh);
//                out.write((char)count);
//            } else {
//                for (int k = 0; k < count; ++k)
//                    out.write(prevCh);
//            }
//
//            if (isEqual) count = 0; else count = 1;
//            prev_r = r; prev_g = g; prev_b = b;
//        }
//        out.close();
//
//        long outputFileLen = new File(outputFilename).length();
//        float compress_ratio = (float)(outputFileLen*100) / (float)fileLen;
//        System.out.println("Compressed File Size : " + outputFileLen + "\n");
//        System.out.println("Compressed Ratio : " + compress_ratio + "% \n");
//    }
}


