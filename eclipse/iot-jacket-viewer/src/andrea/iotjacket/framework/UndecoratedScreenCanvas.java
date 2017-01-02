package andrea.iotjacket.framework;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import andrea.iotjacket.particle.Particle;
import javafx.animation.AnimationTimer;
import javafx.animation.FillTransition;
import javafx.animation.Transition;
import javafx.application.Application;
import javafx.geometry.Rectangle2D;
import javafx.scene.Group;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.effect.BlendMode;
import javafx.scene.layout.Pane;
import javafx.scene.paint.Color;
import javafx.scene.shape.Circle;
import javafx.scene.shape.Shape;
import javafx.stage.Screen;
import javafx.stage.Stage;
import javafx.stage.StageStyle;
import javafx.util.Duration;

//https://examples.javacodegeeks.com/desktop-java/javafx/javafx-animation-example/
public class UndecoratedScreenCanvas extends Application {
	
	public int WIDTH;
	public int HEIGHT;

	protected Rectangle2D primaryScreenBounds = Screen.getPrimary().getVisualBounds();

	private List<Transition> transitions = new ArrayList<>();

	Group root;

	private GraphicsContext g;
	
	Random random = new Random();

	private Parent createContent() {

		Canvas canvas = new Canvas(getScreenWidth(), getScreenHeight());
		g = canvas.getGraphicsContext2D();

		Pane root = new Pane();
		root.setPrefSize(getScreenWidth(), getScreenHeight());
		root.getChildren().add(canvas);

		return root;
	}

	private void onUpdate() {

		clear();

		draw();

	}

	public void clear() {
		g.setGlobalAlpha(1.0);
		g.setGlobalBlendMode(BlendMode.SRC_OVER);
		g.setFill(Color.BLACK);
		g.fillRect(0, 0, getScreenWidth(), getScreenWidth());

	}

	public void render(Particle p) {
		p.render(g);
	}

	@Override
	public void start(Stage primaryStage) {
		
		WIDTH = (int) getScreenWidth();
		HEIGHT = (int) getScreenHeight();
		
		primaryStage.initStyle(StageStyle.UNDECORATED);
		primaryStage.setScene(new Scene(createContent()));
		primaryStage.show();

		AnimationTimer timer = new AnimationTimer() {

			@Override
			public void handle(long now) {
				onUpdate();

			}
		};

		timer.start();
	}

	private void dummy() {
		/*
		 * root = new Group();
		 * 
		 * draw();
		 * 
		 * Scene scene = new Scene(root, getScreenWidth(), getScreenHeight());
		 * 
		 * primaryStage.setScene(scene); primaryStage.show();
		 * 
		 * payAllTransitions();
		 * 
		 * /* FillTransition ft = new FillTransition(Duration.millis(3000),
		 * circle, Color.RED, Color.YELLOW);
		 * 
		 * ft.setCycleCount(40); ft.setAutoReverse(true); ft.play();
		 */
	}

	private void payAllTransitions() {
		for (Transition t : transitions) {
			t.setCycleCount(-1);
			t.setAutoReverse(true);
			t.play();
		}

	}

	public double getScreenWidth() {
		return this.primaryScreenBounds.getWidth();
	}

	public double getScreenHeight() {
		return this.primaryScreenBounds.getHeight();
	}

	public Circle circle(double centerX, double centerY, double radius) {
		;
		Circle circle = new Circle(centerX, centerY, radius);
		root.getChildren().add(circle);
		return circle;
	}

	public void fillTransition(int duration, Shape shape, Color colorFrom, Color colorTo) {

		FillTransition ft = new FillTransition(Duration.millis(duration), shape, colorFrom, colorTo);

		transitions.add(ft);

	}

	protected void draw() {
		circle(100, 100, 50);

	}

	public int random(int value){
		return random.nextInt(value);
	}
}
