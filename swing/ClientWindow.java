import javax.swing.*;

import java.awt.BorderLayout;
import java.awt.event.*;

/**
 * Represents the client window of the application.
 * This class extends the JFrame class and provides a graphical user interface for the client.
 */
class ClientWindow extends JFrame {
  private static final long serialVersionUID = 1L;
  public static Client client;
  JTextArea logTextArea;
  JTextField nameTextField;
  MyLogger logger;

  public static void main(String argv[]) {
    new ClientWindow();
  }

  public ClientWindow() {
    buildScreen();
    logger = new MyLogger(logTextArea);
    startClient();
  }

  private void buildScreen() {
    setTitle("Application");

    logTextArea = new JTextArea(20, 60);
    logTextArea.setEditable(false);

    JScrollPane scrollPane = new JScrollPane(logTextArea);
    scrollPane.setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_ALWAYS);
    add(scrollPane, BorderLayout.CENTER);

    JPanel buttonsContainer = new JPanel();
    nameTextField = new JTextField(30);
    buttonsContainer.add(new JLabel("Media/Group name:"));
    buttonsContainer.add(nameTextField);
    buttonsContainer.add(new JButton(new FindMultimediaAction()));
    buttonsContainer.add(new JButton(new FindGroupAction()));
    buttonsContainer.add(new JButton(new PlayMultimediaAction()));
    buttonsContainer.add(new JButton(new ExitAction()));
    add(buttonsContainer, BorderLayout.SOUTH);

    JMenuBar menuBar = new JMenuBar();
    JMenu menu = new JMenu("Menu");
    menu.add(new JMenuItem(new FindMultimediaAction()));
    menu.add(new JMenuItem(new FindGroupAction()));
    menu.add(new JMenuItem(new PlayMultimediaAction()));
    menu.add(new JMenuItem(new ExitAction()));
    menuBar.add(menu);
    setJMenuBar(menuBar);

    JToolBar toolBar = new JToolBar();
    toolBar.add(new JButton(new FindMultimediaAction()));
    toolBar.add(new JButton(new FindGroupAction()));
    toolBar.add(new JButton(new PlayMultimediaAction()));
    toolBar.add(new JButton(new ExitAction()));
    add(toolBar, BorderLayout.NORTH);

    setDefaultCloseOperation(EXIT_ON_CLOSE);
    setVisible(true);
    pack();
  }

  private void startClient() {
    try {
      logger.log("Connecting to the server...");
      client = new Client();
      logger.log("Connected to server");
    } catch (Exception e) {
      logger.log("Failed to connect to server, open again the application\n");
    }
  }

  class ExitAction extends AbstractAction {
    public ExitAction() {
      putValue(NAME, "Exit");
    }

    public void actionPerformed(ActionEvent e) {
      try {
        if (client != null && client.isConnected()) {
          logger.log("Closing the client...");
          client.close();
        }
        logger.log("Exiting application...");
        System.exit(0);
      } catch (Exception ex) {
        logger.log("Failed to close the client");
      }
    }
  }

  class FindMultimediaAction extends AbstractAction {

    public FindMultimediaAction() {
      putValue(NAME, "Find Multimedia");
    }

    public void actionPerformed(ActionEvent e) {
      try {
        String response = client.send("find multimedia " + nameTextField.getText());
        logger.log(response);
      } catch (Exception ex) {
        logger.log("Failed to find multimedia");
      }
    }
  }

  class PlayMultimediaAction extends AbstractAction {

    public PlayMultimediaAction() {
      putValue(NAME, "Play Multimedia");
    }

    public void actionPerformed(ActionEvent e) {
      try {
        String response = client.send("play multimedia " + nameTextField.getText());
        logger.log(response);
      } catch (Exception ex) {
        logger.log("Failed to play multimedia");
      }
    }
  }

  class DeleteMultimediaAction extends AbstractAction {

    public DeleteMultimediaAction() {
      putValue(NAME, "Delete Multimedia");
    }

    public void actionPerformed(ActionEvent e) {
      try {
        String response = client.send("delete multimedia " + nameTextField.getText());
        logger.log(response);
      } catch (Exception ex) {
        logger.log("Failed to delete multimedia");
      }
    }
  }

  class FindGroupAction extends AbstractAction {

    public FindGroupAction() {
      putValue(NAME, "Find Group");
    }

    public void actionPerformed(ActionEvent e) {
      try {
        String response = client.send("find group " + nameTextField.getText());
        logger.log(response);
      } catch (Exception ex) {
        logger.log("Failed to find group");
      }
    }
  }
}

class MyLogger {
  JTextArea textArea;

  public MyLogger(JTextArea textArea) {
    this.textArea = textArea;
  }

  public void log(String message) {
    textArea.append(message + "\n");
  }
}