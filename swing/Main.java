// http://openbook.galileocomputing.de/javainsel/

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.logging.Logger;
import javax.swing.JButton;
import javax.swing.JFrame;

public class Main {
    public static void main(String[] args) {
        JFrame frame = new JFrame("Das Fenster zur Welt");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 200);

        JButton button1 = new JButton("Klick mich!");
        frame.add(button1);

        button1.addActionListener(new ActionListener() {
            private Logger logger = Logger.getLogger("HelloSwingFrame");

            public void actionPerformed(ActionEvent e) {
                logger.info(e.toString());
            }
        });

        frame.setVisible(true);
    }
}
