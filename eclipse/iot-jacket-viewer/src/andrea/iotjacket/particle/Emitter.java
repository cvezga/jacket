package andrea.iotjacket.particle;

import java.util.List;

public  interface Emitter {

	 List<Particle> emit(double x, double y, double size);
}
