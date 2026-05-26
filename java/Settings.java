import java.awt.*;
import javax.swing.*;

public class Settings extends JFrame {

    private DrawingPanel drawingPanel;

    private Color edgeColor = Color.BLACK;
    private int edgeThickness = 2;

    public enum LabelMode {
        SHOW,
        HOVER,
        HIDE
    }

    private LabelMode labelMode = LabelMode.SHOW;

    public Settings(DrawingPanel drawingPanel) {

        this.drawingPanel = drawingPanel;

        setTitle("Ustawienia");
        setSize(300, 300);
        setLayout(new BorderLayout());
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();

        panel.setLayout(new BoxLayout(panel, BoxLayout.Y_AXIS));

        // ===== KOLOR =====

        JButton colorButton = new JButton("Kolor krawędzi");

        colorButton.addActionListener(e -> {

            Color selected = JColorChooser.showDialog(
                    this,
                    "Wybierz kolor",
                    edgeColor
            );

            if(selected != null) {

                edgeColor = selected;

                drawingPanel.setEdgeColor(edgeColor);
                drawingPanel.repaint();
            }
        });

        panel.add(colorButton);

        // ===== GRUBOŚĆ =====

        panel.add(new JLabel("Grubość krawędzi"));

        JSlider slider = new JSlider(1, 10, edgeThickness);

        slider.setMajorTickSpacing(1);
        slider.setPaintTicks(true);
        slider.setPaintLabels(true);

        slider.addChangeListener(e -> {

    edgeThickness = slider.getValue();

    drawingPanel.setEdgeThickness(edgeThickness);
    drawingPanel.repaint();
});

        panel.add(slider);

        // ===== ETYKIETY =====

        panel.add(new JLabel("Widoczność etykiet"));

        JRadioButton yes = new JRadioButton("Tak");
        JRadioButton hover = new JRadioButton("Po najechaniu");
        JRadioButton no = new JRadioButton("Nie");

        yes.setSelected(true);

        ButtonGroup group = new ButtonGroup();

        group.add(yes);
        group.add(hover);
        group.add(no);

        yes.addActionListener(e -> {

    labelMode = LabelMode.SHOW;

    drawingPanel.setLabelMode(labelMode);
    drawingPanel.repaint();
});

hover.addActionListener(e -> {

    labelMode = LabelMode.HOVER;

    drawingPanel.setLabelMode(labelMode);
    drawingPanel.repaint();
});

no.addActionListener(e -> {

    labelMode = LabelMode.HIDE;

    drawingPanel.setLabelMode(labelMode);
    drawingPanel.repaint();
});

        panel.add(yes);
        panel.add(hover);
        panel.add(no);

        panel.add(Box.createVerticalStrut(10));

        JButton okButton = new JButton("OK");
      okButton.addActionListener(e -> dispose());

        panel.add(okButton);

        add(panel, BorderLayout.CENTER);
    }
}