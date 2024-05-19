import java.io.*;

public class CRLEDecoder implements RLEInterface{

	final private String outputFilename;;

	final private BufferedInputStream in;
	final private BufferedOutputStream out;

	public CRLEDecoder(FileInputStream file, String txt) throws FileNotFoundException {
		in = new BufferedInputStream(file);
		out = new BufferedOutputStream(new FileOutputStream(outputFilename = txt));
	}

	
	public void decodeFile() throws Exception {

        long fileLen = in.available();
        if (fileLen == 0)
			throw new Exception("\nFile is Empty!");

        System.out.println("Compressed File Size : " + fileLen + "\n");
        byte[] signature = new byte[rleSignature.length()];


        in.read(signature,0,rleSignature.length());
        String buf = new String(signature);

        if (!rleSignature.equals(buf))
			throw new Exception("\nNo signature!");

        long i = rleSignature.length();

        while (i < fileLen){
            int ch = in.read();
            i++;
            if (ch == ESCAPECHAR && i < fileLen) {
                ch = in.read();
                int count = in.read();
                i += 2;
                for (int k = 0; k < count; ++k)
					out.write((char)ch);
            } else {
                out.write((char)ch);
            }
        }
        out.close();

        long outputFileLen = new File(outputFilename).length();
        System.out.println("Original File Size : " + outputFileLen + "\n");
	}

    public void decodeFileRGB() throws Exception {

        long fileLen = in.available();
        if (fileLen == 0)
            throw new Exception("\nFile is Empty!");

        System.out.println("Compressed File Size : " + fileLen + "\n");
        byte[] signature = new byte[rleSignature.length()];


        in.read(signature,0,rleSignature.length());
        String buf = new String(signature);

        if (!rleSignature.equals(buf))
            throw new Exception("\nNo signature!");

        long i = rleSignature.length();

        while (i < fileLen){
            int ch = in.read();
            i++;
            if (ch == ESCAPECHAR && i < fileLen) {
                long r = in.read(), g = in.read(), b = in.read();

                int count = in.read();
                i += 4;
                for (int k = 0; k < count; ++k) {
                    out.write((char)r); out.write((char)g); out.write((char)b);
                }
            } else {
                out.write((char)ch);
            }
        }
        out.close();

        long outputFileLen = new File(outputFilename).length();
        System.out.println("Original File Size : " + outputFileLen + "\n");
    }
}