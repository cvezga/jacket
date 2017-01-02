package andrea.iotjacket.particle;

import java.util.ArrayList;
import java.util.List;

import javafx.geometry.Point2D;
import javafx.scene.effect.BlendMode;
import javafx.scene.paint.Color;

public class FireEmitter implements Emitter {

	@Override
	public List<Particle> emit(double x, double y) {
		List<Particle> particles = new ArrayList<>();

		for (int i = 0; i < 5; i++) {
			Particle p = new Particle(x, y, new Point2D(Math.random() - 0.5, Math.random() * -3), 10.0, 1.0, Color.rgb(230,  40,45),
					BlendMode.ADD);
			particles.add(p);
		}
		return particles;
	}

}
