package andrea.iotjacket.viewer;

import java.util.ArrayList;
import java.util.List;

import andrea.iotjacket.framework.UndecoratedScreenCanvas;
import andrea.iotjacket.particle.Emitter;
import andrea.iotjacket.particle.FireEmitter;
import andrea.iotjacket.particle.Particle;
import javafx.application.Application;

public class ViewerCanvas extends UndecoratedScreenCanvas {

	private Emitter emitter = new FireEmitter();

	private List<Particle> particles = new ArrayList<>();

	@Override
	protected void draw() {

		addNewParticles();

		renderAllParticles();

		keepAliveParticles();
	}

	private void addNewParticles() {
		int x = random(WIDTH);
		int y = random(HEIGHT);

		particles.addAll(emitter.emit(x, y));
	}

	private void renderAllParticles() {
		for (Particle p : particles) {
			p.update();
			if (p.isAlive()) {
				render(p);
			}
		}

	}

	

	private void keepAliveParticles() {
		List<Particle> aliveParticles = new ArrayList<>();
		for(Particle p : particles){
			if(p.isAlive()){
				aliveParticles.add(p);
			}
		}
		
		this.particles = aliveParticles;
		
	}

	public static void main(String[] args) {
		Application.launch(args);
	}

}
