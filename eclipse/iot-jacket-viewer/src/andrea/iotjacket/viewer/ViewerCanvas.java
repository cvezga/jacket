package andrea.iotjacket.viewer;

import java.util.ArrayList;
import java.util.List;

import andrea.iotjacket.framework.UndecoratedScreenCanvas;
import andrea.iotjacket.net.UDPBraodcastReader;
import andrea.iotjacket.particle.Emitter;
import andrea.iotjacket.particle.FireEmitter;
import andrea.iotjacket.particle.Particle;
import javafx.application.Application;

public class ViewerCanvas extends UndecoratedScreenCanvas {

	private Emitter emitter = new FireEmitter();

	private List<Particle> particles = new ArrayList<>();
	
    private UDPBraodcastReader udp;
	private Thread t;
	
	private int sensorCount = 0;
	
	public ViewerCanvas(){
		super();
		
		udp = new UDPBraodcastReader(2390,100);
		t = new Thread(udp);
		t.start();
	}

	@Override
	protected void draw() {

		addNewParticles();

		renderAllParticles();

		keepAliveParticles();
	}

	private void addNewParticles() {
		int x = random(WIDTH);
		int y = random(HEIGHT);
		int size = getSensorValue();
		particles.addAll(emitter.emit(x, y, size));
	}
	
	private int getSensorValue(){
		sensorCount++;
		if(sensorCount>100) sensorCount=0;
		int sensorIndex = sensorCount % 6;
		return udp.getSensorValue(sensorIndex);
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
