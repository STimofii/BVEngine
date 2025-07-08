#include "renderer.h"

namespace bulka {
	void Renderer::init() {

	}
	void Renderer::finalization() {

	}
	void Renderer::render(TexturedMesh& mesh) {
		glBindVertexArray(mesh.VAO);
		mesh.getTexture()->bind();
		if (mesh.IBO != 0) {
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.IBO);
			glDrawElements(GL_TRIANGLES, mesh.getIndicesLength(), GL_UNSIGNED_INT, 0);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}
		else {
			glDrawArrays(GL_TRIANGLES, 0, mesh.getPositionsLength() / 5);
		}
		mesh.getTexture()->unbind();

		glBindVertexArray(0);
	}
}