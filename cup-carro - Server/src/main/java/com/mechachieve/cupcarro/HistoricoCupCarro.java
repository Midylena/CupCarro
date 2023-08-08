package com.mechachieve.cupcarro;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;

@Entity
public class HistoricoCupCarro {
	
	private Long id;
	
	private String Classe;
	
	private Long NumClasse;
	
	@Id
	@GeneratedValue(strategy = GenerationType.IDENTITY)
	public Long getId() {
		return id;
	}

	public void setId(Long id) {
		this.id = id;
	}

	public String getClasse() {
		return Classe;
	}

	public void setClasse(String classe) {
		Classe = classe;
	}

	public Long getNumClasse() {
		return NumClasse;
	}

	public void setNumClasse(Long numClasse) {
		NumClasse = numClasse;
	}
}
